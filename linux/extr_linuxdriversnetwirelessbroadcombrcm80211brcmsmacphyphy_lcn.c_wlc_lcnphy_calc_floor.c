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
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static int wlc_lcnphy_calc_floor(s16 coeff_x, int type)
{
	int k;
	k = 0;
	if (type == 0) {
		if (coeff_x < 0)
			k = (coeff_x - 1) / 2;
		else
			k = coeff_x / 2;
	}

	if (type == 1) {
		if ((coeff_x + 1) < 0)
			k = (coeff_x) / 2;
		else
			k = (coeff_x + 1) / 2;
	}
	return k;
}