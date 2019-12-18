#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;

/* Type definitions */
struct TYPE_25__ {void* y; void* x; } ;
struct TYPE_24__ {TYPE_5__ high; TYPE_5__ low; } ;
struct TYPE_23__ {TYPE_18__* p; } ;
struct TYPE_22__ {void* y; void* x; } ;
struct TYPE_21__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Point ;
typedef  TYPE_2__ LSEG ;
typedef  TYPE_3__ BOX ;

/* Variables and functions */
 int /*<<< orphan*/  box_cn (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ box_contain_point (TYPE_3__*,TYPE_18__*) ; 
 int /*<<< orphan*/  box_ov (TYPE_3__*,TYPE_3__*) ; 
 void* float8_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* float8_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseg_closept_point (TYPE_1__*,TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ lseg_interpt_lseg (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  statlseg_construct (TYPE_2__*,TYPE_5__*,TYPE_1__*) ; 

__attribute__((used)) static bool
box_interpt_lseg(Point *result, BOX *box, LSEG *lseg)
{
	BOX			lbox;
	LSEG		bseg;
	Point		point;

	lbox.low.x = float8_min(lseg->p[0].x, lseg->p[1].x);
	lbox.low.y = float8_min(lseg->p[0].y, lseg->p[1].y);
	lbox.high.x = float8_max(lseg->p[0].x, lseg->p[1].x);
	lbox.high.y = float8_max(lseg->p[0].y, lseg->p[1].y);

	/* nothing close to overlap? then not going to intersect */
	if (!box_ov(&lbox, box))
		return false;

	if (result != NULL)
	{
		box_cn(&point, box);
		lseg_closept_point(result, lseg, &point);
	}

	/* an endpoint of segment is inside box? then clearly intersects */
	if (box_contain_point(box, &lseg->p[0]) ||
		box_contain_point(box, &lseg->p[1]))
		return true;

	/* pairwise check lseg intersections */
	point.x = box->low.x;
	point.y = box->high.y;
	statlseg_construct(&bseg, &box->low, &point);
	if (lseg_interpt_lseg(NULL, &bseg, lseg))
		return true;

	statlseg_construct(&bseg, &box->high, &point);
	if (lseg_interpt_lseg(NULL, &bseg, lseg))
		return true;

	point.x = box->high.x;
	point.y = box->low.y;
	statlseg_construct(&bseg, &box->low, &point);
	if (lseg_interpt_lseg(NULL, &bseg, lseg))
		return true;

	statlseg_construct(&bseg, &box->high, &point);
	if (lseg_interpt_lseg(NULL, &bseg, lseg))
		return true;

	/* if we dropped through, no two segs intersected */
	return false;
}