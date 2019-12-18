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
 int /*<<< orphan*/  DatumGetRangeTypeP (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int range_adjacent_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_after_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_before_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_contained_by_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_contains_elem_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_contains_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_eq_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_overlaps_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_overleft_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int range_overright_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
range_gist_consistent_leaf(TypeCacheEntry *typcache, StrategyNumber strategy,
						   const RangeType *key, Datum query)
{
	switch (strategy)
	{
		case RANGESTRAT_BEFORE:
			return range_before_internal(typcache, key,
										 DatumGetRangeTypeP(query));
		case RANGESTRAT_OVERLEFT:
			return range_overleft_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_OVERLAPS:
			return range_overlaps_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_OVERRIGHT:
			return range_overright_internal(typcache, key,
											DatumGetRangeTypeP(query));
		case RANGESTRAT_AFTER:
			return range_after_internal(typcache, key,
										DatumGetRangeTypeP(query));
		case RANGESTRAT_ADJACENT:
			return range_adjacent_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_CONTAINS:
			return range_contains_internal(typcache, key,
										   DatumGetRangeTypeP(query));
		case RANGESTRAT_CONTAINED_BY:
			return range_contained_by_internal(typcache, key,
											   DatumGetRangeTypeP(query));
		case RANGESTRAT_CONTAINS_ELEM:
			return range_contains_elem_internal(typcache, key, query);
		case RANGESTRAT_EQ:
			return range_eq_internal(typcache, key, DatumGetRangeTypeP(query));
		default:
			elog(ERROR, "unrecognized range strategy: %d", strategy);
			return false;		/* keep compiler quiet */
	}
}