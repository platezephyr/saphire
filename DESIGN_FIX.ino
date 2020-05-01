#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <virtuabotixRTC.h>  //RTC library
#include <TouchScreen.h>
#define MINPRESSURE 100
#define MAXPRESSURE 1000


const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x9341
const int TS_LEFT=76,TS_RT=886,TS_TOP=924,TS_BOT=99;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int piksel_x, piksel_y;
bool Touch_getXY(void)
{
TSPoint p = ts.getPoint();
pinMode(YP, OUTPUT);
pinMode(XM, OUTPUT);
digitalWrite(YP, HIGH);
digitalWrite(XM, HIGH);
bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
if (pressed) {
piksel_x = map(p.y, TS_LEFT, TS_RT, 0, tft.width());
piksel_y = map(p.x, TS_TOP, TS_BOT, 0, tft.height());
}
return pressed;
}

#include "DHT.h"
#define DHTPIN 22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#include <dht11.h>
#define dht11PIN 24
#define dht11TYPE DHT11

DHT dht1(dht11PIN, dht11TYPE);

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x5AEB

virtuabotixRTC myRTC(26, 27, 28);
Adafruit_GFX_Button tombolUP1, tombolUP2, tombolDOWN1, tombolDOWN2;
int SET1=35;
int SET2=35;

void setup(void) {
  //myRTC.setDS1302Time(00, 10, 13, 6, 24, 04, 2020);//for update
  
  //creating borders
  tft.reset();
  uint16_t identifier = tft.readID();
  if(identifier==0x0101)identifier=0x9341;
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(1); // Set Rotation at 0 degress (default)
  tft.drawRect(0, 0, 319, 30, GREY);
  tft.fillRect(2, 2, 314, 25, BLACK);
  tft.drawRect(0, 27, 319, 105, GREY);
  tft.fillRect(2, 29, 314, 100, BLACK);
  tft.drawRect(0, 130, 319, 105, GREY);
  tft.fillRect(2, 132, 314, 100, BLACK);


  tombolUP1.initButton (&tft, 240, 115, 30, 20, WHITE, YELLOW, BLACK, "+", 2);
  tombolUP1.drawButton(false);
  tombolDOWN1.initButton (&tft, 290, 115, 30, 20, WHITE, YELLOW, BLACK, "-", 2);
  tombolDOWN1.drawButton(false);
  tombolUP2.initButton (&tft, 240, 220, 30, 20, WHITE, YELLOW, BLACK, "+", 2);
  tombolUP2.drawButton(false);
  tombolDOWN2.initButton (&tft, 290, 220, 30, 20, WHITE, YELLOW, BLACK, "-", 2);
  tombolDOWN2.drawButton(false);

  
 }

void loop(void) {
 
 //showing set point a
  tft.setCursor(250,50);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(3);
  tft.print(SET1);
  //showing set point b
  tft.setCursor(250,150);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(3);
  tft.print(SET2);


  
  bool deteksi = Touch_getXY();
  tombolUP1.press(deteksi && tombolUP1.contains(piksel_x, piksel_y));
  if (tombolUP1.justReleased())
  tombolUP1.drawButton();
  tombolUP2.press(deteksi && tombolUP2.contains(piksel_x, piksel_y));
  if (tombolUP2.justReleased())
  tombolUP2.drawButton();
  tombolDOWN1.press(deteksi && tombolDOWN1.contains(piksel_x, piksel_y));
  if (tombolDOWN1.justReleased())
  tombolDOWN1.drawButton();
  tombolDOWN2.press(deteksi && tombolDOWN2.contains(piksel_x, piksel_y));
  if (tombolDOWN2.justReleased())
  tombolDOWN2.drawButton();



  
  if (tombolUP1.justPressed()) {
  tombolUP1.drawButton(true);
  tft.setCursor (250,50);
  tft.setTextSize (3);
  tft.setTextColor (RED, BLACK);
  tft.print(SET1++);
  }
  if (tombolDOWN1.justPressed()) {
  tombolDOWN1.drawButton(true);
  tft.setCursor (250,50);
  tft.setTextSize (3);
  tft.setTextColor (RED, BLACK);
  tft.print(SET1--);
  }
  if (tombolUP2.justPressed()) {
  tombolUP2.drawButton(true);
  tft.setCursor (250,150);
  tft.setTextSize (3);
  tft.setTextColor (RED, BLACK);
  tft.print(SET2++);
  }
  if (tombolDOWN2.justPressed()) {
  tombolDOWN2.drawButton(true);
  tft.setCursor (250,150);
  tft.setTextSize (3);
  tft.setTextColor (RED, BLACK);
  tft.print(SET2--);
  }
 
  //READ TEMP AND HUMIDITY
  int h= dht.readHumidity();
  float t= dht.readTemperature();
  int h2= dht1.readHumidity();
  float t2= dht1.readTemperature();
  
  tft.setCursor(10, 30);
  tft.setTextColor(RED, BLACK);
  tft.setTextSize(1);
  tft.print("TEMPERATURE");
  tft.setCursor(10, 50);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  tft.print(t2);
  tft.setTextSize(1);
  tft.print("0");
  tft.setTextSize(2);
  tft.print("C");
  tft.setCursor(150, 30);
  tft.setTextColor(RED, BLACK);
  tft.setTextSize(1);
  tft.print("HUMIDITY");
  tft.setCursor(150, 50);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  tft.print(h2);
  tft.setTextSize(2);
  tft.print("%");
  delay(100);
  tft.setCursor(10, 100);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(3);
  tft.print("A");
  
  
  tft.setCursor(10, 135);
  tft.setTextColor(RED, BLACK);
  tft.setTextSize(1);
  tft.print("TEMPERATURE");
  tft.setCursor(10, 150);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  tft.print(t);
  tft.setTextSize(1);
  tft.print("0");
  tft.setTextSize(2);
  tft.print("C");
  tft.setCursor(150, 135);
  tft.setTextColor(RED, BLACK);
  tft.setTextSize(1);
  tft.print("HUMIDITY");
  tft.setCursor(150, 150);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  tft.print(h);
  tft.setTextSize(2);
  tft.print("%");
  delay(100);
  tft.setCursor(10, 200);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(3);
  tft.print("B");

  
  myRTC.updateTime();
  tft.setCursor(2, 4);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(2);
  tft.print(myRTC.dayofmonth);
  tft.print("/");
  tft.print(myRTC.month);
  tft.print("/");
  tft.print(myRTC.year);
  tft.print(" ");
  
  tft.setCursor(195, 4);
  tft.setTextColor(YELLOW, BLACK);
  tft.setTextSize(2);
  tft.print(myRTC.hours);
  tft.print(":");
  tft.print(myRTC.minutes);
  tft.print(":");
  tft.print(myRTC.seconds);
  delay(200);



}


