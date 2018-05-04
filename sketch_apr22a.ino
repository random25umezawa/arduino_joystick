typedef struct t_joyReport {
   int16_t x;
   int16_t y;
   int16_t a1;
   int16_t a2;
   int16_t a3;
   int16_t a4;
   int16_t a5;
   int16_t a6;
   uint32_t buttons;
   int8_t other;
} t_joyReport;

t_joyReport joyReport;

int pre_interval = 0;

int INTERVAL_MILLI = 16;

int rot_arr[4] = {0,1,3,2};

void setup();
void loop();
void sentJoyReport(struct t_joyReport *report);

int x = 0;
int y = 0;

int button1 = 0;

int rx;

void setup()
{
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
   //Serial.begin(9600);
   Serial.begin(115200);
   //delay(200);
   readRotate();
}

void sendJoyReport(struct t_joyReport *report)
{
   Serial.write((uint8_t *)report, sizeof(t_joyReport));
}

void readRotate() {
  int a1 = digitalRead(12);
  int a2 = digitalRead(13);
  int a = rot_arr[a1+a2*2];
  if(a-rx==1||a-rx==-3) x++;
  else if(a-rx==-1||a-rx==3) x--;
  //Serial.print(rx);
  //Serial.print(a);
  //Serial.print(x);
  rx = a;
  //Serial.println(digitalRead(11));
}

void loop()
{
   readRotate();
  button1 = digitalRead(11);
   //delay(2);
   uint32_t button = button1;

   joyReport.a5 = uint16_t(x*125%60000-30000);
   //joyReport.y = 0;
   // Send all buttons in sequence
   joyReport.buttons = button;
    /*
   for (button=0; button<30; button++) {
       joyReport.buttons = 1L<<button;
       sendJoyReport(&joyReport);
       delay(100);
   }
   */
       
       /*
       joyReport.buttons = button1;
       sendJoyReport(&joyReport);
       */

   //joyReport.buttons = 0;
   int new_interval = millis()/INTERVAL_MILLI;
   if(new_interval>pre_interval) sendJoyReport(&joyReport);
   pre_interval = new_interval;
}
