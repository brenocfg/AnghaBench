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
struct TYPE_4__ {void** p; } ;
typedef  void* Point ;
typedef  int /*<<< orphan*/  POLYGON ;
typedef  TYPE_1__ LSEG ;

/* Variables and functions */
 scalar_t__ lseg_contain_point (TYPE_1__*,void**) ; 
 int lseg_inside_poly (void**,void**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ point_eq_point (void**,void**) ; 

__attribute__((used)) static bool
touched_lseg_inside_poly(Point *a, Point *b, LSEG *s, POLYGON *poly, int start)
{
	/* point a is on s, b is not */
	LSEG		t;

	t.p[0] = *a;
	t.p[1] = *b;

	if (point_eq_point(a, s->p))
	{
		if (lseg_contain_point(&t, s->p + 1))
			return lseg_inside_poly(b, s->p + 1, poly, start);
	}
	else if (point_eq_point(a, s->p + 1))
	{
		if (lseg_contain_point(&t, s->p))
			return lseg_inside_poly(b, s->p, poly, start);
	}
	else if (lseg_contain_point(&t, s->p))
	{
		return lseg_inside_poly(b, s->p, poly, start);
	}
	else if (lseg_contain_point(&t, s->p + 1))
	{
		return lseg_inside_poly(b, s->p + 1, poly, start);
	}

	return true;				/* may be not true, but that will check later */
}