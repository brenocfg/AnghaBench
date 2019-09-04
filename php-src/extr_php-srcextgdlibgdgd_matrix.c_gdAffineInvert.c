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
 int GD_FALSE ; 
 int GD_TRUE ; 

int gdAffineInvert (double dst[6], const double src[6])
{
	double r_det = (src[0] * src[3] - src[1] * src[2]);

	if (r_det <= 0.0) {
		return GD_FALSE;
	}

	r_det = 1.0 / r_det;
	dst[0] = src[3] * r_det;
	dst[1] = -src[1] * r_det;
	dst[2] = -src[2] * r_det;
	dst[3] = src[0] * r_det;
	dst[4] = -src[4] * dst[0] - src[5] * dst[2];
	dst[5] = -src[4] * dst[1] - src[5] * dst[3];
	return GD_TRUE;
}