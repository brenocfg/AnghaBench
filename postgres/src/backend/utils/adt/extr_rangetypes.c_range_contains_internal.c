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
typedef  int /*<<< orphan*/  RangeType ;
typedef  int /*<<< orphan*/  RangeBound ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RangeTypeGetOid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ range_cmp_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

bool
range_contains_internal(TypeCacheEntry *typcache, const RangeType *r1, const RangeType *r2)
{
	RangeBound	lower1;
	RangeBound	upper1;
	bool		empty1;
	RangeBound	lower2;
	RangeBound	upper2;
	bool		empty2;

	/* Different types should be prevented by ANYRANGE matching rules */
	if (RangeTypeGetOid(r1) != RangeTypeGetOid(r2))
		elog(ERROR, "range types do not match");

	range_deserialize(typcache, r1, &lower1, &upper1, &empty1);
	range_deserialize(typcache, r2, &lower2, &upper2, &empty2);

	/* If either range is empty, the answer is easy */
	if (empty2)
		return true;
	else if (empty1)
		return false;

	/* Else we must have lower1 <= lower2 and upper1 >= upper2 */
	if (range_cmp_bounds(typcache, &lower1, &lower2) > 0)
		return false;
	if (range_cmp_bounds(typcache, &upper1, &upper2) < 0)
		return false;

	return true;
}