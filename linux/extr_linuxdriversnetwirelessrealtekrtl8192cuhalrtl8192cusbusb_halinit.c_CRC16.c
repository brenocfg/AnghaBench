#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int BIT0 ; 
 int BIT11 ; 
 unsigned short BIT12 ; 
 int BIT15 ; 
 int BIT4 ; 
 unsigned short BIT5 ; 

u16 CRC16(u8 data,u16 CRC)
{
	unsigned char shift_in,CRC_BIT15,DataBit,CRC_BIT11,CRC_BIT4 ;
	int index;
	unsigned short CRC_Result;

	for(index=0;index<8;index++)
	{
		CRC_BIT15=((CRC&BIT15) ? 1:0);
		DataBit  =(data&(BIT0<<index) ? 1:0);
		shift_in=CRC_BIT15^DataBit;
		//printf("CRC_BIT15=%d, DataBit=%d, shift_in=%d \n",CRC_BIT15,DataBit,shift_in);
		
		CRC_Result=CRC<<1;
		//set BIT0 
		//	printf("CRC =%x\n",CRC_Result);
		//CRC bit 0 =shift_in,
		if(shift_in==0)
		{
			CRC_Result&=(~BIT0); 
		}
		else
		{
			CRC_Result|=BIT0;
		}
		//printf("CRC =%x\n",CRC_Result);

		CRC_BIT11 = ((CRC&BIT11) ? 1:0)^shift_in;
		if(CRC_BIT11==0)
		{
			CRC_Result&=(~BIT12); 
		}
		else
		{
			CRC_Result|=BIT12;
		}
		//printf("bit12 CRC =%x\n",CRC_Result);

		CRC_BIT4 = ((CRC&BIT4) ? 1:0)^shift_in;
		if(CRC_BIT4==0)
		{
			CRC_Result&=(~BIT5); 
		}
		else
		{
			CRC_Result|=BIT5;
		}
		//printf("bit5 CRC =%x\n",CRC_Result);

		CRC=CRC_Result; //重複使用上一次的結果
	}

	return CRC;
	
}