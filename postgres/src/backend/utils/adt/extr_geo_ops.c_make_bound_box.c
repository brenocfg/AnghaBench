#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* float8 ;
struct TYPE_9__ {void* y; void* x; } ;
struct TYPE_8__ {void* y; void* x; } ;
struct TYPE_10__ {TYPE_3__ high; TYPE_2__ low; } ;
struct TYPE_11__ {int npts; TYPE_4__ boundbox; TYPE_1__* p; } ;
struct TYPE_7__ {void* y; void* x; } ;
typedef  TYPE_5__ POLYGON ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ float8_gt (void*,void*) ; 
 scalar_t__ float8_lt (void*,void*) ; 

__attribute__((used)) static void
make_bound_box(POLYGON *poly)
{
	int			i;
	float8		x1,
				y1,
				x2,
				y2;

	Assert(poly->npts > 0);

	x1 = x2 = poly->p[0].x;
	y2 = y1 = poly->p[0].y;
	for (i = 1; i < poly->npts; i++)
	{
		if (float8_lt(poly->p[i].x, x1))
			x1 = poly->p[i].x;
		if (float8_gt(poly->p[i].x, x2))
			x2 = poly->p[i].x;
		if (float8_lt(poly->p[i].y, y1))
			y1 = poly->p[i].y;
		if (float8_gt(poly->p[i].y, y2))
			y2 = poly->p[i].y;
	}

	poly->boundbox.low.x = x1;
	poly->boundbox.high.x = x2;
	poly->boundbox.low.y = y1;
	poly->boundbox.high.y = y2;
}