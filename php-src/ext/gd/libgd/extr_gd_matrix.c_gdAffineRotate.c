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
 double const M_PI ; 
 double cos (double const) ; 
 double sin (double const) ; 

int gdAffineRotate (double dst[6], const double angle)
{
	const double sin_t = sin (angle * M_PI / 180.0);
	const double cos_t = cos (angle * M_PI / 180.0);

	dst[0] = cos_t;
	dst[1] = sin_t;
	dst[2] = -sin_t;
	dst[3] = cos_t;
	dst[4] = 0;
	dst[5] = 0;
	return GD_TRUE;
}