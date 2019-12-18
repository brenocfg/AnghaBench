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

int gdAffineFlip (double dst[6], const double src[6], const int flip_h, const int flip_v)
{
	dst[0] = flip_h ? - src[0] : src[0];
	dst[1] = flip_h ? - src[1] : src[1];
	dst[2] = flip_v ? - src[2] : src[2];
	dst[3] = flip_v ? - src[3] : src[3];
	dst[4] = flip_h ? - src[4] : src[4];
	dst[5] = flip_v ? - src[5] : src[5];
	return GD_TRUE;
}