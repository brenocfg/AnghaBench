#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_11__ {void* spl_rdatum; void* spl_ldatum; scalar_t__ spl_nright; scalar_t__ spl_nleft; } ;
struct TYPE_10__ {int n; TYPE_1__* vector; } ;
struct TYPE_9__ {int index; int /*<<< orphan*/  bound; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ SingleBoundSortItem ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  int /*<<< orphan*/  RangeBound ;
typedef  int OffsetNumber ;
typedef  TYPE_3__ GistEntryVector ;
typedef  TYPE_4__ GIST_SPLITVEC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetRangeTypeP (int /*<<< orphan*/ ) ; 
 int FirstOffsetNumber ; 
 int OffsetNumberNext (int) ; 
 int /*<<< orphan*/  PLACE_LEFT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PLACE_RIGHT (int /*<<< orphan*/ *,int) ; 
 void* RangeTypePGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  qsort_arg (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  single_bound_cmp ; 

__attribute__((used)) static void
range_gist_single_sorting_split(TypeCacheEntry *typcache,
								GistEntryVector *entryvec,
								GIST_SPLITVEC *v,
								bool use_upper_bound)
{
	SingleBoundSortItem *sortItems;
	RangeType  *left_range = NULL;
	RangeType  *right_range = NULL;
	OffsetNumber i,
				maxoff,
				split_idx;

	maxoff = entryvec->n - 1;

	sortItems = (SingleBoundSortItem *)
		palloc(maxoff * sizeof(SingleBoundSortItem));

	/*
	 * Prepare auxiliary array and sort the values.
	 */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		RangeType  *range = DatumGetRangeTypeP(entryvec->vector[i].key);
		RangeBound	bound2;
		bool		empty;

		sortItems[i - 1].index = i;
		/* Put appropriate bound into array */
		if (use_upper_bound)
			range_deserialize(typcache, range, &bound2,
							  &sortItems[i - 1].bound, &empty);
		else
			range_deserialize(typcache, range, &sortItems[i - 1].bound,
							  &bound2, &empty);
		Assert(!empty);
	}

	qsort_arg(sortItems, maxoff, sizeof(SingleBoundSortItem),
			  single_bound_cmp, typcache);

	split_idx = maxoff / 2;

	v->spl_nleft = 0;
	v->spl_nright = 0;

	for (i = 0; i < maxoff; i++)
	{
		int			idx = sortItems[i].index;
		RangeType  *range = DatumGetRangeTypeP(entryvec->vector[idx].key);

		if (i < split_idx)
			PLACE_LEFT(range, idx);
		else
			PLACE_RIGHT(range, idx);
	}

	v->spl_ldatum = RangeTypePGetDatum(left_range);
	v->spl_rdatum = RangeTypePGetDatum(right_range);
}