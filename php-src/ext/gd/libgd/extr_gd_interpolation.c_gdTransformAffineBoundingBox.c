#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gdRectPtr ;
struct TYPE_8__ {double x; double y; } ;
typedef  TYPE_2__ gdPointF ;
struct TYPE_7__ {int width; int height; int x; int y; } ;

/* Variables and functions */
 int GD_FALSE ; 
 scalar_t__ GD_TRUE ; 
 scalar_t__ floor (double) ; 
 scalar_t__ gdAffineApplyToPointF (TYPE_2__*,TYPE_2__*,double const*) ; 

int gdTransformAffineBoundingBox(gdRectPtr src, const double affine[6], gdRectPtr bbox)
{
	gdPointF extent[4], min, max, point;
	int i;

	extent[0].x=0.0;
	extent[0].y=0.0;
	extent[1].x=(double) src->width;
	extent[1].y=0.0;
	extent[2].x=(double) src->width;
	extent[2].y=(double) src->height;
	extent[3].x=0.0;
	extent[3].y=(double) src->height;

	for (i=0; i < 4; i++) {
		point=extent[i];
		if (gdAffineApplyToPointF(&extent[i], &point, affine) != GD_TRUE) {
			return GD_FALSE;
		}
	}
	min=extent[0];
	max=extent[0];

	for (i=1; i < 4; i++) {
		if (min.x > extent[i].x)
			min.x=extent[i].x;
		if (min.y > extent[i].y)
			min.y=extent[i].y;
		if (max.x < extent[i].x)
			max.x=extent[i].x;
		if (max.y < extent[i].y)
			max.y=extent[i].y;
	}
	bbox->x = (int) min.x;
	bbox->y = (int) min.y;
	bbox->width  = (int) floor(max.x - min.x) - 1;
	bbox->height = (int) floor(max.y - min.y);
	return GD_TRUE;
}