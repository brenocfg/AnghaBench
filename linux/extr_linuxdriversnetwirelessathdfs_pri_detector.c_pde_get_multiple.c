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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 pde_get_multiple(u32 val, u32 fraction, u32 tolerance)
{
	u32 remainder;
	u32 factor;
	u32 delta;

	if (fraction == 0)
		return 0;

	delta = (val < fraction) ? (fraction - val) : (val - fraction);

	if (delta <= tolerance)
		/* val and fraction are within tolerance */
		return 1;

	factor = val / fraction;
	remainder = val % fraction;
	if (remainder > tolerance) {
		/* no exact match */
		if ((fraction - remainder) <= tolerance)
			/* remainder is within tolerance */
			factor++;
		else
			factor = 0;
	}
	return factor;
}