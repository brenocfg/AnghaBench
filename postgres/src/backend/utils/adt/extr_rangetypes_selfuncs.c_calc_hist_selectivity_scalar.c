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
typedef  int /*<<< orphan*/  TypeCacheEntry ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  RangeBound ;

/* Variables and functions */
 scalar_t__ Max (int,int /*<<< orphan*/ ) ; 
 double get_position (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int rbound_bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static double
calc_hist_selectivity_scalar(TypeCacheEntry *typcache, const RangeBound *constbound,
							 const RangeBound *hist, int hist_nvalues, bool equal)
{
	Selectivity selec;
	int			index;

	/*
	 * Find the histogram bin the given constant falls into. Estimate
	 * selectivity as the number of preceding whole bins.
	 */
	index = rbound_bsearch(typcache, constbound, hist, hist_nvalues, equal);
	selec = (Selectivity) (Max(index, 0)) / (Selectivity) (hist_nvalues - 1);

	/* Adjust using linear interpolation within the bin */
	if (index >= 0 && index < hist_nvalues - 1)
		selec += get_position(typcache, constbound, &hist[index],
							  &hist[index + 1]) / (Selectivity) (hist_nvalues - 1);

	return selec;
}