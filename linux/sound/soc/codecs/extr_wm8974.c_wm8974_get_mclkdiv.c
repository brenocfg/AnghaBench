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
 int WM8974_MCLKDIV_1 ; 
 int WM8974_MCLKDIV_12 ; 
 int WM8974_MCLKDIV_1_5 ; 
 int WM8974_MCLKDIV_2 ; 
 int WM8974_MCLKDIV_3 ; 
 int WM8974_MCLKDIV_4 ; 
 int WM8974_MCLKDIV_6 ; 
 int WM8974_MCLKDIV_8 ; 

__attribute__((used)) static unsigned int wm8974_get_mclkdiv(unsigned int f_in, unsigned int f_out,
				       int *mclkdiv)
{
	unsigned int ratio = 2 * f_in / f_out;

	if (ratio <= 2) {
		*mclkdiv = WM8974_MCLKDIV_1;
		ratio = 2;
	} else if (ratio == 3) {
		*mclkdiv = WM8974_MCLKDIV_1_5;
	} else if (ratio == 4) {
		*mclkdiv = WM8974_MCLKDIV_2;
	} else if (ratio <= 6) {
		*mclkdiv = WM8974_MCLKDIV_3;
		ratio = 6;
	} else if (ratio <= 8) {
		*mclkdiv = WM8974_MCLKDIV_4;
		ratio = 8;
	} else if (ratio <= 12) {
		*mclkdiv = WM8974_MCLKDIV_6;
		ratio = 12;
	} else if (ratio <= 16) {
		*mclkdiv = WM8974_MCLKDIV_8;
		ratio = 16;
	} else {
		*mclkdiv = WM8974_MCLKDIV_12;
		ratio = 24;
	}

	return f_out * ratio / 2;
}