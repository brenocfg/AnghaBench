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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
length_hist_bsearch(Datum *length_hist_values, int length_hist_nvalues,
					double value, bool equal)
{
	int			lower = -1,
				upper = length_hist_nvalues - 1,
				middle;

	while (lower < upper)
	{
		double		middleval;

		middle = (lower + upper + 1) / 2;

		middleval = DatumGetFloat8(length_hist_values[middle]);
		if (middleval < value || (equal && middleval <= value))
			lower = middle;
		else
			upper = middle - 1;
	}
	return lower;
}