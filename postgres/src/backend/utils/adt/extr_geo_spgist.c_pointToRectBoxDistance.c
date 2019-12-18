#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_15__ {scalar_t__ high; } ;
struct TYPE_14__ {scalar_t__ low; } ;
struct TYPE_16__ {TYPE_5__ right; TYPE_4__ left; } ;
struct TYPE_12__ {scalar_t__ high; } ;
struct TYPE_11__ {scalar_t__ low; } ;
struct TYPE_13__ {TYPE_2__ right; TYPE_1__ left; } ;
struct TYPE_17__ {TYPE_6__ range_box_y; TYPE_3__ range_box_x; } ;
typedef  TYPE_7__ RectBox ;
typedef  TYPE_8__ Point ;

/* Variables and functions */
 double HYPOT (double,double) ; 

__attribute__((used)) static double
pointToRectBoxDistance(Point *point, RectBox *rect_box)
{
	double		dx;
	double		dy;

	if (point->x < rect_box->range_box_x.left.low)
		dx = rect_box->range_box_x.left.low - point->x;
	else if (point->x > rect_box->range_box_x.right.high)
		dx = point->x - rect_box->range_box_x.right.high;
	else
		dx = 0;

	if (point->y < rect_box->range_box_y.left.low)
		dy = rect_box->range_box_y.left.low - point->y;
	else if (point->y > rect_box->range_box_y.right.high)
		dy = point->y - rect_box->range_box_y.right.high;
	else
		dy = 0;

	return HYPOT(dx, dy);
}