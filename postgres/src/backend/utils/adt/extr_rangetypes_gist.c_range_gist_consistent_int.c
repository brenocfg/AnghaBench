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
typedef  int StrategyNumber ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  const* DatumGetRangeTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
#define  RANGESTRAT_ADJACENT 137 
#define  RANGESTRAT_AFTER 136 
#define  RANGESTRAT_BEFORE 135 
#define  RANGESTRAT_CONTAINED_BY 134 
#define  RANGESTRAT_CONTAINS 133 
#define  RANGESTRAT_CONTAINS_ELEM 132 
#define  RANGESTRAT_EQ 131 
#define  RANGESTRAT_OVERLAPS 130 
#define  RANGESTRAT_OVERLEFT 129 
#define  RANGESTRAT_OVERRIGHT 128 
 int /*<<< orphan*/  RangeIsEmpty (int /*<<< orphan*/  const*) ; 
 int RangeIsOrContainsEmpty (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  range_adjacent_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  range_after_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  range_before_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int range_contains_elem_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_contains_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int range_overlaps_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  range_overleft_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  range_overright_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
range_gist_consistent_int(TypeCacheEntry *typcache, StrategyNumber strategy,
						  const RangeType *key, Datum query)
{
	switch (strategy)
	{
		case RANGESTRAT_BEFORE:
			if (RangeIsEmpty(key) || RangeIsEmpty(DatumGetRangeTypeP(query)))
				return false;
			return (!range_overright_internal(typcache, key,
											  DatumGetRangeTypeP(query)));
		case RANGESTRAT_OVERLEFT:
			if (RangeIsEmpty(key) || RangeIsEmpty(DatumGetRangeTypeP(query)))
				return false;
			return (!range_after_internal(typcache, key,
										  DatumGetRangeTypeP(query)));
		case RANGESTRAT_OVERLAPS:
			return range_overlaps_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_OVERRIGHT:
			if (RangeIsEmpty(key) || RangeIsEmpty(DatumGetRangeTypeP(query)))
				return false;
			return (!range_before_internal(typcache, key,
										   DatumGetRangeTypeP(query)));
		case RANGESTRAT_AFTER:
			if (RangeIsEmpty(key) || RangeIsEmpty(DatumGetRangeTypeP(query)))
				return false;
			return (!range_overleft_internal(typcache, key,
											 DatumGetRangeTypeP(query)));
		case RANGESTRAT_ADJACENT:
			if (RangeIsEmpty(key) || RangeIsEmpty(DatumGetRangeTypeP(query)))
				return false;
			if (range_adjacent_internal(typcache, key,
										DatumGetRangeTypeP(query)))
				return true;
			return range_overlaps_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_CONTAINS:
			return range_contains_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_CONTAINED_BY:

			/*
			 * Empty ranges are contained by anything, so if key is or
			 * contains any empty ranges, we must descend into it.  Otherwise,
			 * descend only if key overlaps the query.
			 */
			if (RangeIsOrContainsEmpty(key))
				return true;
			return range_overlaps_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_CONTAINS_ELEM:
			return range_contains_elem_internal(typcache, key, query);
		case RANGESTRAT_EQ:

			/*
			 * If query is empty, descend only if the key is or contains any
			 * empty ranges.  Otherwise, descend if key contains query.
			 */
			if (RangeIsEmpty(DatumGetRangeTypeP(query)))
				return RangeIsOrContainsEmpty(key);
			return range_contains_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		default:
			elog(ERROR, "unrecognized range strategy: %d", strategy);
			return false;		/* keep compiler quiet */
	}
}