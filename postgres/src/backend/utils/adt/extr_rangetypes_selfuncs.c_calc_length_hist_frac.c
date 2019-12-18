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
 int /*<<< orphan*/  Assert (int) ; 
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 double get_len_position (double,double,double) ; 
 scalar_t__ isinf (double) ; 
 int length_hist_bsearch (int /*<<< orphan*/ *,int,double,int) ; 

__attribute__((used)) static double
calc_length_hist_frac(Datum *length_hist_values, int length_hist_nvalues,
					  double length1, double length2, bool equal)
{
	double		frac;
	double		A,
				B,
				PA,
				PB;
	double		pos;
	int			i;
	double		area;

	Assert(length2 >= length1);

	if (length2 < 0.0)
		return 0.0;				/* shouldn't happen, but doesn't hurt to check */

	/* All lengths in the table are <= infinite. */
	if (isinf(length2) && equal)
		return 1.0;

	/*----------
	 * The average of a function between A and B can be calculated by the
	 * formula:
	 *
	 *			B
	 *	  1		/
	 * -------	| P(x)dx
	 *	B - A	/
	 *			A
	 *
	 * The geometrical interpretation of the integral is the area under the
	 * graph of P(x). P(x) is defined by the length histogram. We calculate
	 * the area in a piecewise fashion, iterating through the length histogram
	 * bins. Each bin is a trapezoid:
	 *
	 *		 P(x2)
	 *		  /|
	 *		 / |
	 * P(x1)/  |
	 *	   |   |
	 *	   |   |
	 *	---+---+--
	 *	   x1  x2
	 *
	 * where x1 and x2 are the boundaries of the current histogram, and P(x1)
	 * and P(x1) are the cumulative fraction of tuples at the boundaries.
	 *
	 * The area of each trapezoid is 1/2 * (P(x2) + P(x1)) * (x2 - x1)
	 *
	 * The first bin contains the lower bound passed by the caller, so we
	 * use linear interpolation between the previous and next histogram bin
	 * boundary to calculate P(x1). Likewise for the last bin: we use linear
	 * interpolation to calculate P(x2). For the bins in between, x1 and x2
	 * lie on histogram bin boundaries, so P(x1) and P(x2) are simply:
	 * P(x1) =	  (bin index) / (number of bins)
	 * P(x2) = (bin index + 1 / (number of bins)
	 */

	/* First bin, the one that contains lower bound */
	i = length_hist_bsearch(length_hist_values, length_hist_nvalues, length1, equal);
	if (i >= length_hist_nvalues - 1)
		return 1.0;

	if (i < 0)
	{
		i = 0;
		pos = 0.0;
	}
	else
	{
		/* interpolate length1's position in the bin */
		pos = get_len_position(length1,
							   DatumGetFloat8(length_hist_values[i]),
							   DatumGetFloat8(length_hist_values[i + 1]));
	}
	PB = (((double) i) + pos) / (double) (length_hist_nvalues - 1);
	B = length1;

	/*
	 * In the degenerate case that length1 == length2, simply return
	 * P(length1). This is not merely an optimization: if length1 == length2,
	 * we'd divide by zero later on.
	 */
	if (length2 == length1)
		return PB;

	/*
	 * Loop through all the bins, until we hit the last bin, the one that
	 * contains the upper bound. (if lower and upper bounds are in the same
	 * bin, this falls out immediately)
	 */
	area = 0.0;
	for (; i < length_hist_nvalues - 1; i++)
	{
		double		bin_upper = DatumGetFloat8(length_hist_values[i + 1]);

		/* check if we've reached the last bin */
		if (!(bin_upper < length2 || (equal && bin_upper <= length2)))
			break;

		/* the upper bound of previous bin is the lower bound of this bin */
		A = B;
		PA = PB;

		B = bin_upper;
		PB = (double) i / (double) (length_hist_nvalues - 1);

		/*
		 * Add the area of this trapezoid to the total. The point of the
		 * if-check is to avoid NaN, in the corner case that PA == PB == 0,
		 * and B - A == Inf. The area of a zero-height trapezoid (PA == PB ==
		 * 0) is zero, regardless of the width (B - A).
		 */
		if (PA > 0 || PB > 0)
			area += 0.5 * (PB + PA) * (B - A);
	}

	/* Last bin */
	A = B;
	PA = PB;

	B = length2;				/* last bin ends at the query upper bound */
	if (i >= length_hist_nvalues - 1)
		pos = 0.0;
	else
	{
		if (DatumGetFloat8(length_hist_values[i]) == DatumGetFloat8(length_hist_values[i + 1]))
			pos = 0.0;
		else
			pos = get_len_position(length2, DatumGetFloat8(length_hist_values[i]), DatumGetFloat8(length_hist_values[i + 1]));
	}
	PB = (((double) i) + pos) / (double) (length_hist_nvalues - 1);

	if (PA > 0 || PB > 0)
		area += 0.5 * (PB + PA) * (B - A);

	/*
	 * Ok, we have calculated the area, ie. the integral. Divide by width to
	 * get the requested average.
	 *
	 * Avoid NaN arising from infinite / infinite. This happens at least if
	 * length2 is infinite. It's not clear what the correct value would be in
	 * that case, so 0.5 seems as good as any value.
	 */
	if (isinf(area) && isinf(length2))
		frac = 0.5;
	else
		frac = area / (length2 - length1);

	return frac;
}