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
typedef  int /*<<< orphan*/  RangeBound ;

/* Variables and functions */
 int range_cmp_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
rbound_bsearch(TypeCacheEntry *typcache, const RangeBound *value, const RangeBound *hist,
			   int hist_length, bool equal)
{
	int			lower = -1,
				upper = hist_length - 1,
				cmp,
				middle;

	while (lower < upper)
	{
		middle = (lower + upper + 1) / 2;
		cmp = range_cmp_bounds(typcache, &hist[middle], value);

		if (cmp < 0 || (equal && cmp == 0))
			lower = middle;
		else
			upper = middle - 1;
	}
	return lower;
}