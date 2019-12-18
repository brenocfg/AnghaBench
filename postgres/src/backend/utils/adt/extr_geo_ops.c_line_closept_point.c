#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  Point ;
typedef  int /*<<< orphan*/  LINE ;

/* Variables and functions */
 int /*<<< orphan*/  get_float8_nan () ; 
 int /*<<< orphan*/  line_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_interpt_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line_invsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  point_dt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static float8
line_closept_point(Point *result, LINE *line, Point *point)
{
	Point		closept;
	LINE		tmp;

	/*
	 * We drop a perpendicular to find the intersection point.  Ordinarily we
	 * should always find it, but that can fail in the presence of NaN
	 * coordinates, and perhaps even from simple roundoff issues.
	 */
	line_construct(&tmp, point, line_invsl(line));
	if (!line_interpt_line(&closept, &tmp, line))
	{
		if (result != NULL)
			*result = *point;

		return get_float8_nan();
	}

	if (result != NULL)
		*result = closept;

	return point_dt(&closept, point);
}