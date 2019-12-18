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
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATA_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RangeTypeGetOid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * make_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  range_adjacent_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ range_cmp_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  range_overlaps_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RangeType *
range_union_internal(TypeCacheEntry *typcache, RangeType *r1, RangeType *r2,
					 bool strict)
{
	RangeBound	lower1,
				lower2;
	RangeBound	upper1,
				upper2;
	bool		empty1,
				empty2;
	RangeBound *result_lower;
	RangeBound *result_upper;

	/* Different types should be prevented by ANYRANGE matching rules */
	if (RangeTypeGetOid(r1) != RangeTypeGetOid(r2))
		elog(ERROR, "range types do not match");

	range_deserialize(typcache, r1, &lower1, &upper1, &empty1);
	range_deserialize(typcache, r2, &lower2, &upper2, &empty2);

	/* if either is empty, the other is the correct answer */
	if (empty1)
		return r2;
	if (empty2)
		return r1;

	if (strict &&
		!DatumGetBool(range_overlaps_internal(typcache, r1, r2)) &&
		!DatumGetBool(range_adjacent_internal(typcache, r1, r2)))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_EXCEPTION),
				 errmsg("result of range union would not be contiguous")));

	if (range_cmp_bounds(typcache, &lower1, &lower2) < 0)
		result_lower = &lower1;
	else
		result_lower = &lower2;

	if (range_cmp_bounds(typcache, &upper1, &upper2) > 0)
		result_upper = &upper1;
	else
		result_upper = &upper2;

	return make_range(typcache, result_lower, result_upper, false);
}