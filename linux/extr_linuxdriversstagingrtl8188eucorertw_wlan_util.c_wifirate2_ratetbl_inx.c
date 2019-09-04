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

__attribute__((used)) static int wifirate2_ratetbl_inx(unsigned char rate)
{
	rate = rate & 0x7f;

	switch (rate) {
	case 54*2:
		return 11;
	case 48*2:
		return 10;
	case 36*2:
		return 9;
	case 24*2:
		return 8;
	case 18*2:
		return 7;
	case 12*2:
		return 6;
	case 9*2:
		return 5;
	case 6*2:
		return 4;
	case 11*2:
		return 3;
	case 11:
		return 2;
	case 2*2:
		return 1;
	case 1*2:
		return 0;
	default:
		return 0;
	}
}