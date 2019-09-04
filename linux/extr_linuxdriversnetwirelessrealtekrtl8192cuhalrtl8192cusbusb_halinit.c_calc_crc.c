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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;

/* Variables and functions */
 int CRC16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

u16 calc_crc(u8 * pdata,int length)
{
//    unsigned char data[2]={0xC6,0xAA};
	u16 CRC=0xffff;
	int i;
	
	for(i=0;i<length;i++)
	{
		CRC=CRC16(pdata[i],CRC);
	}

	CRC=~CRC;                  //¨ú¸É¼Æ
	printk("CRC =%x\n",CRC);
	return CRC;
}