#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_1__ LSEG ;
typedef  int /*<<< orphan*/  LINE ;

/* Variables and functions */
 int /*<<< orphan*/  line_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_interpt_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseg_contain_point (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseg_sl (TYPE_1__*) ; 
 scalar_t__ point_eq_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
lseg_interpt_line(Point *result, LSEG *lseg, LINE *line)
{
	Point		interpt;
	LINE		tmp;

	/*
	 * First, we promote the line segment to a line, because we know how to
	 * find the intersection point of two lines.  If they don't have an
	 * intersection point, we are done.
	 */
	line_construct(&tmp, &lseg->p[0], lseg_sl(lseg));
	if (!line_interpt_line(&interpt, &tmp, line))
		return false;

	/*
	 * Then, we check whether the intersection point is actually on the line
	 * segment.
	 */
	if (!lseg_contain_point(lseg, &interpt))
		return false;
	if (result != NULL)
	{
		/*
		 * If there is an intersection, then check explicitly for matching
		 * endpoints since there may be rounding effects with annoying LSB
		 * residue.
		 */
		if (point_eq_point(&lseg->p[0], &interpt))
			*result = lseg->p[0];
		else if (point_eq_point(&lseg->p[1], &interpt))
			*result = lseg->p[1];
		else
			*result = interpt;
	}

	return true;
}