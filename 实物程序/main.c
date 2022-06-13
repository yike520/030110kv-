#include <reg51.H>
#define uchar unsigned char 
#define uint  unsigned int
uchar cp,cp1;
uint ad0,vale = 0,temp_x;
sbit P10=P1^0;
sbit P11=P1^1;
sbit P14=P1^4;
float temp,I_vale,I_vale2[10],Izz = 0,temp_s = 20;
#include <uart.c>
#include <PCF8591.c>
#include <stdio.h>				//启用printf，将printf重映射到串口

bit bit1=0,flag;
#include <stdio.h>				//启用printf，将printf重映射到串口
void Timer_isr(void)interrupt 1
{
	
	
		TH0 =0xf7;
	TL0 =0x5c;
	cp++;

	
	if(cp >= 200)
	{
		
		cp = 0;
		cp1++;
			
		if(cp1 >= 6)
		{
		ad0 = read_pcf8591(0x40);
		I_vale  = 	(float)	 ad0 *5/255;
		 temp  =  (I_vale -2.5125)*34*10/1.6;
			I_vale2[vale] = I_vale;
			vale++;
			if(vale >= 10)	 vale = 0;
			cp1 = 0;
			
		}
	}
	
}
void Timer_Init()
{
		TMOD = 0x01;
	TH0 =0xf7;
	TL0 =0x5c;

	TR0 = 1;

	ET0 = 1;

	EA =1;
}
  void delayus(uint x)  //延时函数
{
	while(x--);
}
void main()
{
	Timer_Init();
//	 init_1602();
//	LCD_clr1602();
//	delayus(20000);
	  uart_init();
	 init_24c04();
//	DS18B20_init();
		  TI = 1;
//	  temp = get_temp();
//	  temp = get_temp();
	while(1)
	{
		 
		if(P10 == 0)
		{
			while(P10 == 0);
			temp_s++;
			if(temp_s>=200)			temp_s=200;
		}
	   	if(P11 == 0)
		{
			while(P11 == 0);
			temp_s--;
			if(temp_s<=0)			temp_s=0;
		}
if(temp >= temp_s) P14 =0;
		else P14 =1;
	 TI = 1;
		 printf("\r\ntemp:%f",temp);
		printf("\r\ntemp_s:%f",temp_s);
		   TI = 0;
		   	 TI = 1;
	    printf("\r\nI:%f",I_vale);
		  TI = 0;
	
		delayus(20000);
	  
	 
	
	}
}
