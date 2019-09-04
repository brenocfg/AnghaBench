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

__attribute__((used)) static int da9052_bat_interpolate(int vbat_lower, int  vbat_upper,
				   int level_lower, int level_upper,
				   int bat_voltage)
{
	int tmp;

	tmp = ((level_upper - level_lower) * 1000) / (vbat_upper - vbat_lower);
	tmp = level_lower + (((bat_voltage - vbat_lower) * tmp) / 1000);

	return tmp;
}