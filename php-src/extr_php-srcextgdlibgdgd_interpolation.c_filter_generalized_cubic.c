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
 double DEFAULT_FILTER_GENERALIZED_CUBIC ; 
 scalar_t__ fabs (double const) ; 

__attribute__((used)) static double filter_generalized_cubic(const double t)
{
	const double a = -DEFAULT_FILTER_GENERALIZED_CUBIC;
	double abs_t = (double)fabs(t);
	double abs_t_sq = abs_t * abs_t;
	if (abs_t < 1) return (a + 2) * abs_t_sq * abs_t - (a + 3) * abs_t_sq + 1;
	if (abs_t < 2) return a * abs_t_sq * abs_t - 5 * a * abs_t_sq + 8 * a * abs_t - 4 * a;
	return 0;
}