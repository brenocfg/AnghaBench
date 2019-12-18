#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_8__ {scalar_t__ lower; } ;
typedef  TYPE_1__ RangeBound ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  bounds_adjacent (int /*<<< orphan*/ *,TYPE_1__ const,TYPE_1__ const) ; 
 int range_cmp_bounds (int /*<<< orphan*/ *,TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static int
adjacent_cmp_bounds(TypeCacheEntry *typcache, const RangeBound *arg,
					const RangeBound *centroid)
{
	int			cmp;

	Assert(arg->lower != centroid->lower);

	cmp = range_cmp_bounds(typcache, arg, centroid);

	if (centroid->lower)
	{
		/*------
		 * The argument is an upper bound, we are searching for adjacent lower
		 * bounds. A matching adjacent lower bound must be *larger* than the
		 * argument, but only just.
		 *
		 * The following table illustrates the desired result with a fixed
		 * argument bound, and different centroids. The CMP column shows
		 * the value of 'cmp' variable, and ADJ shows whether the argument
		 * and centroid are adjacent, per bounds_adjacent(). (N) means we
		 * don't need to check for that case, because it's implied by CMP.
		 * With the argument range [..., 500), the adjacent range we're
		 * searching for is [500, ...):
		 *
		 *	ARGUMENT   CENTROID		CMP   ADJ
		 *	[..., 500) [498, ...)	 >	  (N)	[500, ...) is to the right
		 *	[..., 500) [499, ...)	 =	  (N)	[500, ...) is to the right
		 *	[..., 500) [500, ...)	 <	   Y	[500, ...) is to the right
		 *	[..., 500) [501, ...)	 <	   N	[500, ...) is to the left
		 *
		 * So, we must search left when the argument is smaller than, and not
		 * adjacent, to the centroid. Otherwise search right.
		 *------
		 */
		if (cmp < 0 && !bounds_adjacent(typcache, *arg, *centroid))
			return -1;
		else
			return 1;
	}
	else
	{
		/*------
		 * The argument is a lower bound, we are searching for adjacent upper
		 * bounds. A matching adjacent upper bound must be *smaller* than the
		 * argument, but only just.
		 *
		 *	ARGUMENT   CENTROID		CMP   ADJ
		 *	[500, ...) [..., 499)	 >	  (N)	[..., 500) is to the right
		 *	[500, ...) [..., 500)	 >	  (Y)	[..., 500) is to the right
		 *	[500, ...) [..., 501)	 =	  (N)	[..., 500) is to the left
		 *	[500, ...) [..., 502)	 <	  (N)	[..., 500) is to the left
		 *
		 * We must search left when the argument is smaller than or equal to
		 * the centroid. Otherwise search right. We don't need to check
		 * whether the argument is adjacent with the centroid, because it
		 * doesn't matter.
		 *------
		 */
		if (cmp <= 0)
			return -1;
		else
			return 1;
	}
}