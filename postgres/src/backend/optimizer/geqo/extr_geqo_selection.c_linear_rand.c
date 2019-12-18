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
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 double geqo_rand (int /*<<< orphan*/ *) ; 
 double sqrt (double) ; 

__attribute__((used)) static int
linear_rand(PlannerInfo *root, int pool_size, double bias)
{
	double		index;			/* index between 0 and pool_size */
	double		max = (double) pool_size;

	/*
	 * If geqo_rand() returns exactly 1.0 then we will get exactly max from
	 * this equation, whereas we need 0 <= index < max.  Also it seems
	 * possible that roundoff error might deliver values slightly outside the
	 * range; in particular avoid passing a value slightly less than 0 to
	 * sqrt(). If we get a bad value just try again.
	 */
	do
	{
		double		sqrtval;

		sqrtval = (bias * bias) - 4.0 * (bias - 1.0) * geqo_rand(root);
		if (sqrtval > 0.0)
			sqrtval = sqrt(sqrtval);
		index = max * (bias - sqrtval) / 2.0 / (bias - 1.0);
	} while (index < 0.0 || index >= max);

	return (int) index;
}