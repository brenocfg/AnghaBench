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
 double astro_revolution (double) ; 

__attribute__((used)) static double astro_GMST0(double d)
{
	double sidtim0;
	/* Sidtime at 0h UT = L (Sun's mean longitude) + 180.0 degr  */
	/* L = M + w, as defined in sunpos().  Since I'm too lazy to */
	/* add these numbers, I'll let the C compiler do it for me.  */
	/* Any decent C compiler will add the constants at compile   */
	/* time, imposing no runtime or code overhead.               */
	sidtim0 = astro_revolution((180.0 + 356.0470 + 282.9404) + (0.9856002585 + 4.70935E-5) * d);
	return sidtim0;
}