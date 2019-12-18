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
 int GD_TRUE ; 

int gdAffineScale (double dst[6], const double scale_x, const double scale_y)
{
	dst[0] = scale_x;
	dst[1] = 0;
	dst[2] = 0;
	dst[3] = scale_y;
	dst[4] = 0;
	dst[5] = 0;
	return GD_TRUE;
}