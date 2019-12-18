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
typedef  double float8 ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {TYPE_1__* p; } ;
struct TYPE_8__ {int npts; TYPE_4__* p; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_2__ POLYGON ;
typedef  TYPE_3__ LSEG ;

/* Variables and functions */
 scalar_t__ float8_lt (double,double) ; 
 double lseg_closept_point (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ point_inside (int /*<<< orphan*/ *,int,TYPE_4__*) ; 

__attribute__((used)) static float8
dist_ppoly_internal(Point *pt, POLYGON *poly)
{
	float8		result;
	float8		d;
	int			i;
	LSEG		seg;

	if (point_inside(pt, poly->npts, poly->p) != 0)
		return 0.0;

	/* initialize distance with segment between first and last points */
	seg.p[0].x = poly->p[0].x;
	seg.p[0].y = poly->p[0].y;
	seg.p[1].x = poly->p[poly->npts - 1].x;
	seg.p[1].y = poly->p[poly->npts - 1].y;
	result = lseg_closept_point(NULL, &seg, pt);

	/* check distances for other segments */
	for (i = 0; i < poly->npts - 1; i++)
	{
		seg.p[0].x = poly->p[i].x;
		seg.p[0].y = poly->p[i].y;
		seg.p[1].x = poly->p[i + 1].x;
		seg.p[1].y = poly->p[i + 1].y;
		d = lseg_closept_point(NULL, &seg, pt);
		if (float8_lt(d, result))
			result = d;
	}

	return result;
}