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
typedef  int /*<<< orphan*/  Point ;

/* Variables and functions */
 scalar_t__ point_eq_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
plist_same(int npts, Point *p1, Point *p2)
{
	int			i,
				ii,
				j;

	/* find match for first point */
	for (i = 0; i < npts; i++)
	{
		if (point_eq_point(&p2[i], &p1[0]))
		{

			/* match found? then look forward through remaining points */
			for (ii = 1, j = i + 1; ii < npts; ii++, j++)
			{
				if (j >= npts)
					j = 0;
				if (!point_eq_point(&p2[j], &p1[ii]))
					break;
			}
			if (ii == npts)
				return true;

			/* match not found forwards? then look backwards */
			for (ii = 1, j = i - 1; ii < npts; ii++, j--)
			{
				if (j < 0)
					j = (npts - 1);
				if (!point_eq_point(&p2[j], &p1[ii]))
					break;
			}
			if (ii == npts)
				return true;
		}
	}

	return false;
}