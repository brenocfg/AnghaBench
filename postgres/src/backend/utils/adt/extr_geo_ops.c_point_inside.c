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
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int POINT_ON_POLYGON ; 
 int /*<<< orphan*/  float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lseg_crossing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
point_inside(Point *p, int npts, Point *plist)
{
	float8		x0,
				y0;
	float8		prev_x,
				prev_y;
	int			i = 0;
	float8		x,
				y;
	int			cross,
				total_cross = 0;

	Assert(npts > 0);

	/* compute first polygon point relative to single point */
	x0 = float8_mi(plist[0].x, p->x);
	y0 = float8_mi(plist[0].y, p->y);

	prev_x = x0;
	prev_y = y0;
	/* loop over polygon points and aggregate total_cross */
	for (i = 1; i < npts; i++)
	{
		/* compute next polygon point relative to single point */
		x = float8_mi(plist[i].x, p->x);
		y = float8_mi(plist[i].y, p->y);

		/* compute previous to current point crossing */
		if ((cross = lseg_crossing(x, y, prev_x, prev_y)) == POINT_ON_POLYGON)
			return 2;
		total_cross += cross;

		prev_x = x;
		prev_y = y;
	}

	/* now do the first point */
	if ((cross = lseg_crossing(x0, y0, prev_x, prev_y)) == POINT_ON_POLYGON)
		return 2;
	total_cross += cross;

	if (total_cross != 0)
		return 1;
	return 0;
}