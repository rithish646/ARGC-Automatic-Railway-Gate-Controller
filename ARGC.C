#include <pic.h>
__CONFIG(0x3F72);
#define _XTAL_FREQ 4000000

#define IR1_PIN RC4  
#define IR2_PIN RC5  

#define Servo1_PIN RC6 
#define Servo2_PIN RC7 

#define REDLED1    RB0
#define GREENLED1  RB2
#define REDLED2    RB3
#define GREENLED2  RB5

#define RS RC0
#define RW RC1
#define EN RC2
void command(unsigned char y)
{
PORTD=y;
RS=0;
RW=0;
EN=1;
__delay_ms(1);
EN=0;
}
void data(unsigned char z)
{
PORTD=z;
RS=1;
RW=0;
EN=1;
__delay_ms(1);
EN=0;
}
void initial()
{
command(0x38);
command(0x01);
command(0x06);
command(0x0C);
}

void servoRotate0(void) //0 Degree
{
  //unsigned int i;
  //for(i=0;i<50;i++)
  //{
    Servo1_PIN = 1;
	Servo2_PIN = 1;
    __delay_us(800);
    Servo1_PIN = 0;
	Servo2_PIN = 0;
    __delay_us(19200);
  //}
}

void servoRotate90(void) //90 Degree
{
  //unsigned int i;
  //for(i=0;i<50;i++)
  //{
    Servo1_PIN = 1;
	Servo2_PIN = 1;
    __delay_us(1500);
    Servo1_PIN = 0;
	Servo2_PIN = 0;
    __delay_us(18500);
  //}
}

void main()
{
TRISB=0x00;
PORTB=0x00;
TRISD=0x00;
PORTB=0x00;
TRISC=0x30;
PORTC=0x00;
while(1)
{
if(IR1_PIN==0)
{
REDLED1=REDLED2=1;
servoRotate0();
GREENLED1=GREENLED2=0;
initial();
char a[]={" ELECTRO-PSYCHS "};
command(0x80);
for(int i=0;i<=15;i++)
{
data(a[i]);
}
char b[]={" TRAIN REACHING "};
command(0xC0);
for(int j=0;j<=19;j++)
{
data(b[j]);
}
__delay_ms(1000);
}
if(IR2_PIN==0)
{
REDLED1=REDLED2=0;
__delay_ms(1000);
GREENLED1=GREENLED2=1;
initial();
char c[]={" ELECTRO-PSYCHS "};
command(0x80);
for(int k=0;k<=15;k++)
{
data(c[k]);
}
char d[]={"   TRAIN LEFT "};
command(0xC0);
for(int l=0;l<=13;l++)
{
data(d[l]);
}
__delay_ms(1000);
servoRotate90();
}
}
}