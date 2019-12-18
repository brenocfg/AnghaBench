#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  double float8 ;
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {TYPE_3__ high; TYPE_3__ low; } ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Point ;
typedef  int /*<<< orphan*/  LSEG ;
typedef  TYPE_2__ BOX ;

/* Variables and functions */
 scalar_t__ box_contain_point (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ float8_lt (double,double) ; 
 double lseg_closept_point (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  statlseg_construct (int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static float8
box_closept_point(Point *result, BOX *box, Point *pt)
{
	float8		dist,
				d;
	Point		point,
				closept;
	LSEG		lseg;

	if (box_contain_point(box, pt))
	{
		if (result != NULL)
			*result = *pt;

		return 0.0;
	}

	/* pairwise check lseg distances */
	point.x = box->low.x;
	point.y = box->high.y;
	statlseg_construct(&lseg, &box->low, &point);
	dist = lseg_closept_point(result, &lseg, pt);

	statlseg_construct(&lseg, &box->high, &point);
	d = lseg_closept_point(&closept, &lseg, pt);
	if (float8_lt(d, dist))
	{
		dist = d;
		if (result != NULL)
			*result = closept;
	}

	point.x = box->high.x;
	point.y = box->low.y;
	statlseg_construct(&lseg, &box->low, &point);
	d = lseg_closept_point(&closept, &lseg, pt);
	if (float8_lt(d, dist))
	{
		dist = d;
		if (result != NULL)
			*result = closept;
	}

	statlseg_construct(&lseg, &box->high, &point);
	d = lseg_closept_point(&closept, &lseg, pt);
	if (float8_lt(d, dist))
	{
		dist = d;
		if (result != NULL)
			*result = closept;
	}

	return dist;
}