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
typedef  int int16 ;
typedef  int /*<<< orphan*/  TypeCacheEntry ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  int /*<<< orphan*/  RangeBound ;

/* Variables and functions */
 scalar_t__ range_cmp_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int16
getQuadrant(TypeCacheEntry *typcache, const RangeType *centroid, const RangeType *tst)
{
	RangeBound	centroidLower,
				centroidUpper;
	bool		centroidEmpty;
	RangeBound	lower,
				upper;
	bool		empty;

	range_deserialize(typcache, centroid, &centroidLower, &centroidUpper,
					  &centroidEmpty);
	range_deserialize(typcache, tst, &lower, &upper, &empty);

	if (empty)
		return 5;

	if (range_cmp_bounds(typcache, &lower, &centroidLower) >= 0)
	{
		if (range_cmp_bounds(typcache, &upper, &centroidUpper) >= 0)
			return 1;
		else
			return 2;
	}
	else
	{
		if (range_cmp_bounds(typcache, &upper, &centroidUpper) >= 0)
			return 4;
		else
			return 3;
	}
}