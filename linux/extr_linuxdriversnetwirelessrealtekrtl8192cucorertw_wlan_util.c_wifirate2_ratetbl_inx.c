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

/* Variables and functions */

int wifirate2_ratetbl_inx(unsigned char rate)
{
	int	inx = 0;
	rate = rate & 0x7f;

	switch (rate) 
	{
		case 54*2:
			inx = 11;
			break;

		case 48*2:
			inx = 10;
			break;

		case 36*2:
			inx = 9;
			break;

		case 24*2:
			inx = 8;
			break;
			
		case 18*2:
			inx = 7;
			break;

		case 12*2:
			inx = 6;
			break;

		case 9*2:
			inx = 5;
			break;
			
		case 6*2:
			inx = 4;
			break;

		case 11*2:
			inx = 3;
			break;
		case 11:
			inx = 2;
			break;

		case 2*2:
			inx = 1;
			break;
		
		case 1*2:
			inx = 0;
			break;

	}
	return inx;	
}