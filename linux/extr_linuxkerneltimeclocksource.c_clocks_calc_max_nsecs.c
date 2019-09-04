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
typedef  int u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ULLONG_MAX ; 
 int clocksource_cyc2ns (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 
 int min (int,int) ; 

u64 clocks_calc_max_nsecs(u32 mult, u32 shift, u32 maxadj, u64 mask, u64 *max_cyc)
{
	u64 max_nsecs, max_cycles;

	/*
	 * Calculate the maximum number of cycles that we can pass to the
	 * cyc2ns() function without overflowing a 64-bit result.
	 */
	max_cycles = ULLONG_MAX;
	do_div(max_cycles, mult+maxadj);

	/*
	 * The actual maximum number of cycles we can defer the clocksource is
	 * determined by the minimum of max_cycles and mask.
	 * Note: Here we subtract the maxadj to make sure we don't sleep for
	 * too long if there's a large negative adjustment.
	 */
	max_cycles = min(max_cycles, mask);
	max_nsecs = clocksource_cyc2ns(max_cycles, mult - maxadj, shift);

	/* return the max_cycles value as well if requested */
	if (max_cyc)
		*max_cyc = max_cycles;

	/* Return 50% of the actual maximum, so we can detect bad values */
	max_nsecs >>= 1;

	return max_nsecs;
}