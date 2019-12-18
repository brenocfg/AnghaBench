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
typedef  int /*<<< orphan*/  TypeCacheEntry ;
typedef  int /*<<< orphan*/  RangeBound ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 double calc_length_hist_frac (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_distance (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 double get_position (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int rbound_bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static double
calc_hist_selectivity_contains(TypeCacheEntry *typcache,
							   const RangeBound *lower, const RangeBound *upper,
							   const RangeBound *hist_lower, int hist_nvalues,
							   Datum *length_hist_values, int length_hist_nvalues)
{
	int			i,
				lower_index;
	double		bin_width,
				lower_bin_width;
	double		sum_frac;
	float8		prev_dist;

	/* Find the bin containing the lower bound of query range. */
	lower_index = rbound_bsearch(typcache, lower, hist_lower, hist_nvalues,
								 true);

	/*
	 * Calculate lower_bin_width, ie. the fraction of the of (lower_index,
	 * lower_index + 1) bin which is greater than lower bound of query range
	 * using linear interpolation of subdiff function.
	 */
	if (lower_index >= 0 && lower_index < hist_nvalues - 1)
		lower_bin_width = get_position(typcache, lower, &hist_lower[lower_index],
									   &hist_lower[lower_index + 1]);
	else
		lower_bin_width = 0.0;

	/*
	 * Loop through all the lower bound bins, smaller than the query lower
	 * bound. In the loop, dist and prev_dist are the distance of the
	 * "current" bin's lower and upper bounds from the constant upper bound.
	 * We begin from query lower bound, and walk backwards, so the first bin's
	 * upper bound is the query lower bound, and its distance to the query
	 * upper bound is the length of the query range.
	 *
	 * bin_width represents the width of the current bin. Normally it is 1.0,
	 * meaning a full width bin, except for the first bin, which is only
	 * counted up to the constant lower bound.
	 */
	prev_dist = get_distance(typcache, lower, upper);
	sum_frac = 0.0;
	bin_width = lower_bin_width;
	for (i = lower_index; i >= 0; i--)
	{
		float8		dist;
		double		length_hist_frac;

		/*
		 * dist -- distance from upper bound of query range to current value
		 * of lower bound histogram or lower bound of query range (if we've
		 * reach it).
		 */
		dist = get_distance(typcache, &hist_lower[i], upper);

		/*
		 * Get average fraction of length histogram which covers intervals
		 * longer than (or equal to) distance to upper bound of query range.
		 */
		length_hist_frac =
			1.0 - calc_length_hist_frac(length_hist_values,
										length_hist_nvalues,
										prev_dist, dist, false);

		sum_frac += length_hist_frac * bin_width / (double) (hist_nvalues - 1);

		bin_width = 1.0;
		prev_dist = dist;
	}

	return sum_frac;
}