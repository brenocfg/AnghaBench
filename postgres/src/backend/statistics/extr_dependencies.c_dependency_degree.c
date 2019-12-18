#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tupDesc; int /*<<< orphan*/  attrcollid; int /*<<< orphan*/  attrtypid; } ;
typedef  TYPE_1__ VacAttrStats ;
struct TYPE_6__ {scalar_t__ lt_opr; } ;
typedef  TYPE_2__ TypeCacheEntry ;
typedef  size_t SortItem ;
typedef  size_t* MultiSortSupport ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  size_t AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  TYPECACHE_LT_OPR ; 
 size_t* build_attnums_array (int /*<<< orphan*/ *,int*) ; 
 size_t* build_sorted_items (int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int,size_t*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multi_sort_add_dimension (size_t*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ multi_sort_compare_dim (int,size_t*,size_t*,size_t*) ; 
 scalar_t__ multi_sort_compare_dims (int /*<<< orphan*/ ,int,size_t*,size_t*,size_t*) ; 
 size_t* multi_sort_init (int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (size_t*) ; 

__attribute__((used)) static double
dependency_degree(int numrows, HeapTuple *rows, int k, AttrNumber *dependency,
				  VacAttrStats **stats, Bitmapset *attrs)
{
	int			i,
				nitems;
	MultiSortSupport mss;
	SortItem   *items;
	AttrNumber *attnums;
	AttrNumber *attnums_dep;
	int			numattrs;

	/* counters valid within a group */
	int			group_size = 0;
	int			n_violations = 0;

	/* total number of rows supporting (consistent with) the dependency */
	int			n_supporting_rows = 0;

	/* Make sure we have at least two input attributes. */
	Assert(k >= 2);

	/* sort info for all attributes columns */
	mss = multi_sort_init(k);

	/*
	 * Transform the attrs from bitmap to an array to make accessing the i-th
	 * member easier, and then construct a filtered version with only attnums
	 * referenced by the dependency we validate.
	 */
	attnums = build_attnums_array(attrs, &numattrs);

	attnums_dep = (AttrNumber *) palloc(k * sizeof(AttrNumber));
	for (i = 0; i < k; i++)
		attnums_dep[i] = attnums[dependency[i]];

	/*
	 * Verify the dependency (a,b,...)->z, using a rather simple algorithm:
	 *
	 * (a) sort the data lexicographically
	 *
	 * (b) split the data into groups by first (k-1) columns
	 *
	 * (c) for each group count different values in the last column
	 *
	 * We use the column data types' default sort operators and collations;
	 * perhaps at some point it'd be worth using column-specific collations?
	 */

	/* prepare the sort function for the dimensions */
	for (i = 0; i < k; i++)
	{
		VacAttrStats *colstat = stats[dependency[i]];
		TypeCacheEntry *type;

		type = lookup_type_cache(colstat->attrtypid, TYPECACHE_LT_OPR);
		if (type->lt_opr == InvalidOid) /* shouldn't happen */
			elog(ERROR, "cache lookup failed for ordering operator for type %u",
				 colstat->attrtypid);

		/* prepare the sort function for this dimension */
		multi_sort_add_dimension(mss, i, type->lt_opr, colstat->attrcollid);
	}

	/*
	 * build an array of SortItem(s) sorted using the multi-sort support
	 *
	 * XXX This relies on all stats entries pointing to the same tuple
	 * descriptor.  For now that assumption holds, but it might change in the
	 * future for example if we support statistics on multiple tables.
	 */
	items = build_sorted_items(numrows, &nitems, rows, stats[0]->tupDesc,
							   mss, k, attnums_dep);

	/*
	 * Walk through the sorted array, split it into rows according to the
	 * first (k-1) columns. If there's a single value in the last column, we
	 * count the group as 'supporting' the functional dependency. Otherwise we
	 * count it as contradicting.
	 */

	/* start with the first row forming a group */
	group_size = 1;

	/* loop 1 beyond the end of the array so that we count the final group */
	for (i = 1; i <= nitems; i++)
	{
		/*
		 * Check if the group ended, which may be either because we processed
		 * all the items (i==nitems), or because the i-th item is not equal to
		 * the preceding one.
		 */
		if (i == nitems ||
			multi_sort_compare_dims(0, k - 2, &items[i - 1], &items[i], mss) != 0)
		{
			/*
			 * If no violations were found in the group then track the rows of
			 * the group as supporting the functional dependency.
			 */
			if (n_violations == 0)
				n_supporting_rows += group_size;

			/* Reset counters for the new group */
			n_violations = 0;
			group_size = 1;
			continue;
		}
		/* first columns match, but the last one does not (so contradicting) */
		else if (multi_sort_compare_dim(k - 1, &items[i - 1], &items[i], mss) != 0)
			n_violations++;

		group_size++;
	}

	if (items)
		pfree(items);

	pfree(mss);
	pfree(attnums);
	pfree(attnums_dep);

	/* Compute the 'degree of validity' as (supporting/total). */
	return (n_supporting_rows * 1.0 / numrows);
}