#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdPointFPtr ;
struct TYPE_4__ {double x; double y; } ;

/* Variables and functions */
 int GD_TRUE ; 

int gdAffineApplyToPointF (gdPointFPtr dst, const gdPointFPtr src,
		  const double affine[6])
{
	double x = src->x;
	double y = src->y;
	x = src->x;
	y = src->y;
	dst->x = x * affine[0] + y * affine[2] + affine[4];
	dst->y = x * affine[1] + y * affine[3] + affine[5];
	return GD_TRUE;
}