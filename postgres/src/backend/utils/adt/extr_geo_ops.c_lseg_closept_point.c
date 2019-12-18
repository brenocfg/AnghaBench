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
typedef  int /*<<< orphan*/  float8 ;
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_1__ LSEG ;
typedef  int /*<<< orphan*/  LINE ;

/* Variables and functions */
 int /*<<< orphan*/  line_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseg_closept_line (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  point_dt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  point_invsl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static float8
lseg_closept_point(Point *result, LSEG *lseg, Point *pt)
{
	Point		closept;
	LINE		tmp;

	/*
	 * To find the closest point, we draw a perpendicular line from the point
	 * to the line segment.
	 */
	line_construct(&tmp, pt, point_invsl(&lseg->p[0], &lseg->p[1]));
	lseg_closept_line(&closept, lseg, &tmp);

	if (result != NULL)
		*result = closept;

	return point_dt(&closept, pt);
}