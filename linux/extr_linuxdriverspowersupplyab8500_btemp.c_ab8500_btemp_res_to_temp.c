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
struct abx500_res_to_temp {int resist; int temp; } ;
struct ab8500_btemp {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ab8500_btemp_res_to_temp(struct ab8500_btemp *di,
	const struct abx500_res_to_temp *tbl, int tbl_size, int res)
{
	int i;
	/*
	 * Calculate the formula for the straight line
	 * Simple interpolation if we are within
	 * the resistance table limits, extrapolate
	 * if resistance is outside the limits.
	 */
	if (res > tbl[0].resist)
		i = 0;
	else if (res <= tbl[tbl_size - 1].resist)
		i = tbl_size - 2;
	else {
		i = 0;
		while (!(res <= tbl[i].resist &&
			res > tbl[i + 1].resist))
			i++;
	}

	return tbl[i].temp + ((tbl[i + 1].temp - tbl[i].temp) *
		(res - tbl[i].resist)) / (tbl[i + 1].resist - tbl[i].resist);
}