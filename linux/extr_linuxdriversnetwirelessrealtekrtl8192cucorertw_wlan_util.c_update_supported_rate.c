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
 unsigned int NumRates ; 
 int wifirate2_ratetbl_inx (unsigned char) ; 

unsigned int update_supported_rate(unsigned char *ptn, unsigned int ptn_sz)
{
	unsigned int i, num_of_rate;
	unsigned int mask = 0;
	
	num_of_rate = (ptn_sz > NumRates)? NumRates: ptn_sz;
		
	for (i = 0; i < num_of_rate; i++)
	{
		mask |= 0x1 << wifirate2_ratetbl_inx(*(ptn + i));
	}

	return mask;
}