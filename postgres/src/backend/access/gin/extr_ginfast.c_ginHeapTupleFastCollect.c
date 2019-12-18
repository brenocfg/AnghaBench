#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_8__ {int ntuples; int lentuples; int /*<<< orphan*/  sumsize; TYPE_1__** tuples; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__ GinTupleCollector ;
typedef  int /*<<< orphan*/  GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GinFormTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IndexTupleSize (TYPE_1__*) ; 
 int MaxAllocSize ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ginExtractEntries (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ **) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ repalloc (TYPE_1__**,int) ; 

void
ginHeapTupleFastCollect(GinState *ginstate,
						GinTupleCollector *collector,
						OffsetNumber attnum, Datum value, bool isNull,
						ItemPointer ht_ctid)
{
	Datum	   *entries;
	GinNullCategory *categories;
	int32		i,
				nentries;

	/*
	 * Extract the key values that need to be inserted in the index
	 */
	entries = ginExtractEntries(ginstate, attnum, value, isNull,
								&nentries, &categories);

	/*
	 * Protect against integer overflow in allocation calculations
	 */
	if (nentries < 0 ||
		collector->ntuples + nentries > MaxAllocSize / sizeof(IndexTuple))
		elog(ERROR, "too many entries for GIN index");

	/*
	 * Allocate/reallocate memory for storing collected tuples
	 */
	if (collector->tuples == NULL)
	{
		/*
		 * Determine the number of elements to allocate in the tuples array
		 * initially.  Make it a power of 2 to avoid wasting memory when
		 * resizing (since palloc likes powers of 2).
		 */
		collector->lentuples = 16;
		while (collector->lentuples < nentries)
			collector->lentuples *= 2;

		collector->tuples = (IndexTuple *) palloc(sizeof(IndexTuple) * collector->lentuples);
	}
	else if (collector->lentuples < collector->ntuples + nentries)
	{
		/*
		 * Advance lentuples to the next suitable power of 2.  This won't
		 * overflow, though we could get to a value that exceeds
		 * MaxAllocSize/sizeof(IndexTuple), causing an error in repalloc.
		 */
		do
		{
			collector->lentuples *= 2;
		} while (collector->lentuples < collector->ntuples + nentries);

		collector->tuples = (IndexTuple *) repalloc(collector->tuples,
													sizeof(IndexTuple) * collector->lentuples);
	}

	/*
	 * Build an index tuple for each key value, and add to array.  In pending
	 * tuples we just stick the heap TID into t_tid.
	 */
	for (i = 0; i < nentries; i++)
	{
		IndexTuple	itup;

		itup = GinFormTuple(ginstate, attnum, entries[i], categories[i],
							NULL, 0, 0, true);
		itup->t_tid = *ht_ctid;
		collector->tuples[collector->ntuples++] = itup;
		collector->sumsize += IndexTupleSize(itup);
	}
}