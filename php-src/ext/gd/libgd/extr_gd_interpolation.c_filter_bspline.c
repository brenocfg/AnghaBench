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

__attribute__((used)) static double filter_bspline(const double x)
{
	if (x>2.0f) {
		return 0.0f;
	} else {
		double a, b, c, d;
		/* Was calculated anyway cause the "if((x-1.0f) < 0)" */
		const double xm1 = x - 1.0f;
		const double xp1 = x + 1.0f;
		const double xp2 = x + 2.0f;

		if ((xp2) <= 0.0f) a = 0.0f; else a = xp2*xp2*xp2;
		if ((xp1) <= 0.0f) b = 0.0f; else b = xp1*xp1*xp1;
		if (x <= 0) c = 0.0f; else c = x*x*x;
		if ((xm1) <= 0.0f) d = 0.0f; else d = xm1*xm1*xm1;

		return (0.16666666666666666667f * (a - (4.0f * b) + (6.0f * c) - (4.0f * d)));
	}
}