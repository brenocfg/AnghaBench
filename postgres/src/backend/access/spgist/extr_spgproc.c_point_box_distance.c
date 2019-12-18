#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_10__ {TYPE_2__ high; TYPE_1__ low; } ;
struct TYPE_9__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_3__ Point ;
typedef  TYPE_4__ BOX ;

/* Variables and functions */
 double HYPOT (double,double) ; 
 double get_float8_nan () ; 
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static double
point_box_distance(Point *point, BOX *box)
{
	double		dx,
				dy;

	if (isnan(point->x) || isnan(box->low.x) ||
		isnan(point->y) || isnan(box->low.y))
		return get_float8_nan();

	if (point->x < box->low.x)
		dx = box->low.x - point->x;
	else if (point->x > box->high.x)
		dx = point->x - box->high.x;
	else
		dx = 0.0;

	if (point->y < box->low.y)
		dy = box->low.y - point->y;
	else if (point->y > box->high.y)
		dy = point->y - box->high.y;
	else
		dy = 0.0;

	return HYPOT(dx, dy);
}