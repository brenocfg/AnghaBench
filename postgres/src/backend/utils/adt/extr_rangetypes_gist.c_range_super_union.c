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
 char RANGE_CONTAIN_EMPTY ; 
 char RANGE_EMPTY ; 
 int /*<<< orphan*/ * make_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rangeCopy (int /*<<< orphan*/ *) ; 
 scalar_t__ range_cmp_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 char range_get_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_set_contain_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RangeType *
range_super_union(TypeCacheEntry *typcache, RangeType *r1, RangeType *r2)
{
	RangeType  *result;
	RangeBound	lower1,
				lower2;
	RangeBound	upper1,
				upper2;
	bool		empty1,
				empty2;
	char		flags1,
				flags2;
	RangeBound *result_lower;
	RangeBound *result_upper;

	range_deserialize(typcache, r1, &lower1, &upper1, &empty1);
	range_deserialize(typcache, r2, &lower2, &upper2, &empty2);
	flags1 = range_get_flags(r1);
	flags2 = range_get_flags(r2);

	if (empty1)
	{
		/* We can return r2 as-is if it already is or contains empty */
		if (flags2 & (RANGE_EMPTY | RANGE_CONTAIN_EMPTY))
			return r2;
		/* Else we'd better copy it (modify-in-place isn't safe) */
		r2 = rangeCopy(r2);
		range_set_contain_empty(r2);
		return r2;
	}
	if (empty2)
	{
		/* We can return r1 as-is if it already is or contains empty */
		if (flags1 & (RANGE_EMPTY | RANGE_CONTAIN_EMPTY))
			return r1;
		/* Else we'd better copy it (modify-in-place isn't safe) */
		r1 = rangeCopy(r1);
		range_set_contain_empty(r1);
		return r1;
	}

	if (range_cmp_bounds(typcache, &lower1, &lower2) <= 0)
		result_lower = &lower1;
	else
		result_lower = &lower2;

	if (range_cmp_bounds(typcache, &upper1, &upper2) >= 0)
		result_upper = &upper1;
	else
		result_upper = &upper2;

	/* optimization to avoid constructing a new range */
	if (result_lower == &lower1 && result_upper == &upper1 &&
		((flags1 & RANGE_CONTAIN_EMPTY) || !(flags2 & RANGE_CONTAIN_EMPTY)))
		return r1;
	if (result_lower == &lower2 && result_upper == &upper2 &&
		((flags2 & RANGE_CONTAIN_EMPTY) || !(flags1 & RANGE_CONTAIN_EMPTY)))
		return r2;

	result = make_range(typcache, result_lower, result_upper, false);

	if ((flags1 & RANGE_CONTAIN_EMPTY) || (flags2 & RANGE_CONTAIN_EMPTY))
		range_set_contain_empty(result);

	return result;
}