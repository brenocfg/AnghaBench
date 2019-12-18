#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_34__ {TYPE_1__ rng_subdiff_finfo; } ;
typedef  TYPE_3__ TypeCacheEntry ;
struct TYPE_40__ {size_t index; scalar_t__ delta; } ;
struct TYPE_39__ {int entries_count; int first; size_t common_left; TYPE_4__* right_lower; TYPE_4__* left_upper; scalar_t__ has_subtype_diff; TYPE_3__* typcache; } ;
struct TYPE_38__ {size_t* spl_left; size_t* spl_right; void* spl_rdatum; void* spl_ldatum; scalar_t__ spl_nright; scalar_t__ spl_nleft; } ;
struct TYPE_37__ {size_t n; TYPE_2__* vector; } ;
struct TYPE_35__ {int /*<<< orphan*/  val; } ;
struct TYPE_36__ {TYPE_4__ lower; TYPE_4__ upper; } ;
struct TYPE_33__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  TYPE_4__ RangeBound ;
typedef  size_t OffsetNumber ;
typedef  TYPE_5__ NonEmptyRange ;
typedef  TYPE_6__ GistEntryVector ;
typedef  TYPE_7__ GIST_SPLITVEC ;
typedef  TYPE_8__ ConsiderSplitContext ;
typedef  TYPE_9__ CommonEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetRangeTypeP (int /*<<< orphan*/ ) ; 
 size_t FirstOffsetNumber ; 
 size_t OffsetNumberNext (size_t) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLACE_LEFT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PLACE_RIGHT (int /*<<< orphan*/ *,int) ; 
 void* PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ call_subtype_diff (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_entry_cmp ; 
 int /*<<< orphan*/  interval_cmp_lower ; 
 int /*<<< orphan*/  interval_cmp_upper ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  qsort (TYPE_9__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_arg (TYPE_5__*,int,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ range_cmp_bounds (TYPE_3__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  range_deserialize (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,int*) ; 
 int /*<<< orphan*/  range_gist_consider_split (TYPE_8__*,TYPE_4__*,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  range_gist_fallback_split (TYPE_3__*,TYPE_6__*,TYPE_7__*) ; 

__attribute__((used)) static void
range_gist_double_sorting_split(TypeCacheEntry *typcache,
								GistEntryVector *entryvec,
								GIST_SPLITVEC *v)
{
	ConsiderSplitContext context;
	OffsetNumber i,
				maxoff;
	RangeType  *range,
			   *left_range = NULL,
			   *right_range = NULL;
	int			common_entries_count;
	NonEmptyRange *by_lower,
			   *by_upper;
	CommonEntry *common_entries;
	int			nentries,
				i1,
				i2;
	RangeBound *right_lower,
			   *left_upper;

	memset(&context, 0, sizeof(ConsiderSplitContext));
	context.typcache = typcache;
	context.has_subtype_diff = OidIsValid(typcache->rng_subdiff_finfo.fn_oid);

	maxoff = entryvec->n - 1;
	nentries = context.entries_count = maxoff - FirstOffsetNumber + 1;
	context.first = true;

	/* Allocate arrays for sorted range bounds */
	by_lower = (NonEmptyRange *) palloc(nentries * sizeof(NonEmptyRange));
	by_upper = (NonEmptyRange *) palloc(nentries * sizeof(NonEmptyRange));

	/* Fill arrays of bounds */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		RangeType  *range = DatumGetRangeTypeP(entryvec->vector[i].key);
		bool		empty;

		range_deserialize(typcache, range,
						  &by_lower[i - FirstOffsetNumber].lower,
						  &by_lower[i - FirstOffsetNumber].upper,
						  &empty);
		Assert(!empty);
	}

	/*
	 * Make two arrays of range bounds: one sorted by lower bound and another
	 * sorted by upper bound.
	 */
	memcpy(by_upper, by_lower, nentries * sizeof(NonEmptyRange));
	qsort_arg(by_lower, nentries, sizeof(NonEmptyRange),
			  interval_cmp_lower, typcache);
	qsort_arg(by_upper, nentries, sizeof(NonEmptyRange),
			  interval_cmp_upper, typcache);

	/*----------
	 * The goal is to form a left and right range, so that every entry
	 * range is contained by either left or right interval (or both).
	 *
	 * For example, with the ranges (0,1), (1,3), (2,3), (2,4):
	 *
	 * 0 1 2 3 4
	 * +-+
	 *	 +---+
	 *	   +-+
	 *	   +---+
	 *
	 * The left and right ranges are of the form (0,a) and (b,4).
	 * We first consider splits where b is the lower bound of an entry.
	 * We iterate through all entries, and for each b, calculate the
	 * smallest possible a. Then we consider splits where a is the
	 * upper bound of an entry, and for each a, calculate the greatest
	 * possible b.
	 *
	 * In the above example, the first loop would consider splits:
	 * b=0: (0,1)-(0,4)
	 * b=1: (0,1)-(1,4)
	 * b=2: (0,3)-(2,4)
	 *
	 * And the second loop:
	 * a=1: (0,1)-(1,4)
	 * a=3: (0,3)-(2,4)
	 * a=4: (0,4)-(2,4)
	 *----------
	 */

	/*
	 * Iterate over lower bound of right group, finding smallest possible
	 * upper bound of left group.
	 */
	i1 = 0;
	i2 = 0;
	right_lower = &by_lower[i1].lower;
	left_upper = &by_upper[i2].lower;
	while (true)
	{
		/*
		 * Find next lower bound of right group.
		 */
		while (i1 < nentries &&
			   range_cmp_bounds(typcache, right_lower,
								&by_lower[i1].lower) == 0)
		{
			if (range_cmp_bounds(typcache, &by_lower[i1].upper,
								 left_upper) > 0)
				left_upper = &by_lower[i1].upper;
			i1++;
		}
		if (i1 >= nentries)
			break;
		right_lower = &by_lower[i1].lower;

		/*
		 * Find count of ranges which anyway should be placed to the left
		 * group.
		 */
		while (i2 < nentries &&
			   range_cmp_bounds(typcache, &by_upper[i2].upper,
								left_upper) <= 0)
			i2++;

		/*
		 * Consider found split to see if it's better than what we had.
		 */
		range_gist_consider_split(&context, right_lower, i1, left_upper, i2);
	}

	/*
	 * Iterate over upper bound of left group finding greatest possible lower
	 * bound of right group.
	 */
	i1 = nentries - 1;
	i2 = nentries - 1;
	right_lower = &by_lower[i1].upper;
	left_upper = &by_upper[i2].upper;
	while (true)
	{
		/*
		 * Find next upper bound of left group.
		 */
		while (i2 >= 0 &&
			   range_cmp_bounds(typcache, left_upper,
								&by_upper[i2].upper) == 0)
		{
			if (range_cmp_bounds(typcache, &by_upper[i2].lower,
								 right_lower) < 0)
				right_lower = &by_upper[i2].lower;
			i2--;
		}
		if (i2 < 0)
			break;
		left_upper = &by_upper[i2].upper;

		/*
		 * Find count of intervals which anyway should be placed to the right
		 * group.
		 */
		while (i1 >= 0 &&
			   range_cmp_bounds(typcache, &by_lower[i1].lower,
								right_lower) >= 0)
			i1--;

		/*
		 * Consider found split to see if it's better than what we had.
		 */
		range_gist_consider_split(&context, right_lower, i1 + 1,
								  left_upper, i2 + 1);
	}

	/*
	 * If we failed to find any acceptable splits, use trivial split.
	 */
	if (context.first)
	{
		range_gist_fallback_split(typcache, entryvec, v);
		return;
	}

	/*
	 * Ok, we have now selected bounds of the groups. Now we have to
	 * distribute entries themselves. At first we distribute entries which can
	 * be placed unambiguously and collect "common entries" to array.
	 */

	/* Allocate vectors for results */
	v->spl_left = (OffsetNumber *) palloc(nentries * sizeof(OffsetNumber));
	v->spl_right = (OffsetNumber *) palloc(nentries * sizeof(OffsetNumber));
	v->spl_nleft = 0;
	v->spl_nright = 0;

	/*
	 * Allocate an array for "common entries" - entries which can be placed to
	 * either group without affecting overlap along selected axis.
	 */
	common_entries_count = 0;
	common_entries = (CommonEntry *) palloc(nentries * sizeof(CommonEntry));

	/*
	 * Distribute entries which can be distributed unambiguously, and collect
	 * common entries.
	 */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		RangeBound	lower,
					upper;
		bool		empty;

		/*
		 * Get upper and lower bounds along selected axis.
		 */
		range = DatumGetRangeTypeP(entryvec->vector[i].key);

		range_deserialize(typcache, range, &lower, &upper, &empty);

		if (range_cmp_bounds(typcache, &upper, context.left_upper) <= 0)
		{
			/* Fits in the left group */
			if (range_cmp_bounds(typcache, &lower, context.right_lower) >= 0)
			{
				/* Fits also in the right group, so "common entry" */
				common_entries[common_entries_count].index = i;
				if (context.has_subtype_diff)
				{
					/*
					 * delta = (lower - context.right_lower) -
					 * (context.left_upper - upper)
					 */
					common_entries[common_entries_count].delta =
						call_subtype_diff(typcache,
										  lower.val,
										  context.right_lower->val) -
						call_subtype_diff(typcache,
										  context.left_upper->val,
										  upper.val);
				}
				else
				{
					/* Without subtype_diff, take all deltas as zero */
					common_entries[common_entries_count].delta = 0;
				}
				common_entries_count++;
			}
			else
			{
				/* Doesn't fit to the right group, so join to the left group */
				PLACE_LEFT(range, i);
			}
		}
		else
		{
			/*
			 * Each entry should fit on either left or right group. Since this
			 * entry didn't fit in the left group, it better fit in the right
			 * group.
			 */
			Assert(range_cmp_bounds(typcache, &lower,
									context.right_lower) >= 0);
			PLACE_RIGHT(range, i);
		}
	}

	/*
	 * Distribute "common entries", if any.
	 */
	if (common_entries_count > 0)
	{
		/*
		 * Sort "common entries" by calculated deltas in order to distribute
		 * the most ambiguous entries first.
		 */
		qsort(common_entries, common_entries_count, sizeof(CommonEntry),
			  common_entry_cmp);

		/*
		 * Distribute "common entries" between groups according to sorting.
		 */
		for (i = 0; i < common_entries_count; i++)
		{
			int			idx = common_entries[i].index;

			range = DatumGetRangeTypeP(entryvec->vector[idx].key);

			/*
			 * Check if we have to place this entry in either group to achieve
			 * LIMIT_RATIO.
			 */
			if (i < context.common_left)
				PLACE_LEFT(range, idx);
			else
				PLACE_RIGHT(range, idx);
		}
	}

	v->spl_ldatum = PointerGetDatum(left_range);
	v->spl_rdatum = PointerGetDatum(right_range);
}