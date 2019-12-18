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
typedef  double float8 ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_8__ {TYPE_1__ low; TYPE_1__ high; } ;
typedef  TYPE_1__ Point ;
typedef  TYPE_2__ BOX ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 double float8_mi (scalar_t__,scalar_t__) ; 
 double point_point_distance (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static float8
computeDistance(bool isLeaf, BOX *box, Point *point)
{
	float8		result = 0.0;

	if (isLeaf)
	{
		/* simple point to point distance */
		result = point_point_distance(point, &box->low);
	}
	else if (point->x <= box->high.x && point->x >= box->low.x &&
			 point->y <= box->high.y && point->y >= box->low.y)
	{
		/* point inside the box */
		result = 0.0;
	}
	else if (point->x <= box->high.x && point->x >= box->low.x)
	{
		/* point is over or below box */
		Assert(box->low.y <= box->high.y);
		if (point->y > box->high.y)
			result = float8_mi(point->y, box->high.y);
		else if (point->y < box->low.y)
			result = float8_mi(box->low.y, point->y);
		else
			elog(ERROR, "inconsistent point values");
	}
	else if (point->y <= box->high.y && point->y >= box->low.y)
	{
		/* point is to left or right of box */
		Assert(box->low.x <= box->high.x);
		if (point->x > box->high.x)
			result = float8_mi(point->x, box->high.x);
		else if (point->x < box->low.x)
			result = float8_mi(box->low.x, point->x);
		else
			elog(ERROR, "inconsistent point values");
	}
	else
	{
		/* closest point will be a vertex */
		Point		p;
		float8		subresult;

		result = point_point_distance(point, &box->low);

		subresult = point_point_distance(point, &box->high);
		if (result > subresult)
			result = subresult;

		p.x = box->low.x;
		p.y = box->high.y;
		subresult = point_point_distance(point, &p);
		if (result > subresult)
			result = subresult;

		p.x = box->high.x;
		p.y = box->low.y;
		subresult = point_point_distance(point, &p);
		if (result > subresult)
			result = subresult;
	}

	return result;
}