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
typedef  int uchar ;

/* Variables and functions */
 int WD33C93_FS_12_15 ; 
 int WD33C93_FS_16_20 ; 
 int WD33C93_FS_8_10 ; 

__attribute__((used)) static uchar
set_clk_freq(int freq, int *mhz)
{
	int x = freq;
	if (WD33C93_FS_8_10 == freq)
		freq = 8;
	else if (WD33C93_FS_12_15 == freq)
		freq = 12;
	else if (WD33C93_FS_16_20 == freq)
		freq = 16;
	else if (freq > 7 && freq < 11)
		x = WD33C93_FS_8_10;
		else if (freq > 11 && freq < 16)
		x = WD33C93_FS_12_15;
		else if (freq > 15 && freq < 21)
		x = WD33C93_FS_16_20;
	else {
			/* Hmm, wouldn't it be safer to assume highest freq here? */
		x = WD33C93_FS_8_10;
		freq = 8;
	}
	*mhz = freq;
	return x;
}