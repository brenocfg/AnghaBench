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
 scalar_t__ isinf (double) ; 

__attribute__((used)) static double
get_len_position(double value, double hist1, double hist2)
{
	if (!isinf(hist1) && !isinf(hist2))
	{
		/*
		 * Both bounds are finite. The value should be finite too, because it
		 * lies somewhere between the bounds. If it doesn't, just return
		 * something.
		 */
		if (isinf(value))
			return 0.5;

		return 1.0 - (hist2 - value) / (hist2 - hist1);
	}
	else if (isinf(hist1) && !isinf(hist2))
	{
		/*
		 * Lower bin boundary is -infinite, upper is finite. Return 1.0 to
		 * indicate the value is infinitely far from the lower bound.
		 */
		return 1.0;
	}
	else if (isinf(hist1) && isinf(hist2))
	{
		/* same as above, but in reverse */
		return 0.0;
	}
	else
	{
		/*
		 * If both bin boundaries are infinite, they should be equal to each
		 * other, and the value should also be infinite and equal to both
		 * bounds. (But don't Assert that, to avoid crashing unnecessarily if
		 * the caller messes up)
		 *
		 * Assume the value to lie in the middle of the infinite bounds.
		 */
		return 0.5;
	}
}