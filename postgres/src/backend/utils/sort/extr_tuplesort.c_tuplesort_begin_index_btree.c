#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_11__ {int nKeys; int abbrevNext; int enforceUnique; TYPE_2__* sortKeys; void* indexRel; void* heapRel; int /*<<< orphan*/  readtup; int /*<<< orphan*/  writetup; int /*<<< orphan*/  copytup; int /*<<< orphan*/  comparetup; int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_14__ {TYPE_3__* scankeys; } ;
struct TYPE_13__ {int sk_flags; scalar_t__ sk_attno; int /*<<< orphan*/  sk_collation; } ;
struct TYPE_12__ {int ssup_nulls_first; scalar_t__ ssup_attno; int abbreviate; int /*<<< orphan*/  ssup_collation; int /*<<< orphan*/  ssup_cxt; } ;
typedef  int /*<<< orphan*/  SortSupportData ;
typedef  TYPE_2__* SortSupport ;
typedef  int /*<<< orphan*/  SortCoordinate ;
typedef  TYPE_3__* ScanKey ;
typedef  void* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__* BTScanInsert ;

/* Variables and functions */
 int /*<<< orphan*/  AssertState (int) ; 
 int /*<<< orphan*/  BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  BTLessStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  INDEX_SORT ; 
 int IndexRelationGetNumberOfKeyAttributes (void*) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARALLEL_SORT (TYPE_1__*) ; 
 int /*<<< orphan*/  PrepareSortSupportFromIndexRel (void*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int SK_BT_DESC ; 
 int SK_BT_NULLS_FIRST ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SORT_START (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* _bt_mkscankey (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comparetup_index_btree ; 
 int /*<<< orphan*/  copytup_index ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char,int,char) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_4__*) ; 
 int /*<<< orphan*/  readtup_index ; 
 scalar_t__ trace_sort ; 
 TYPE_1__* tuplesort_begin_common (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writetup_index ; 

Tuplesortstate *
tuplesort_begin_index_btree(Relation heapRel,
							Relation indexRel,
							bool enforceUnique,
							int workMem,
							SortCoordinate coordinate,
							bool randomAccess)
{
	Tuplesortstate *state = tuplesort_begin_common(workMem, coordinate,
												   randomAccess);
	BTScanInsert indexScanKey;
	MemoryContext oldcontext;
	int			i;

	oldcontext = MemoryContextSwitchTo(state->sortcontext);

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG,
			 "begin index sort: unique = %c, workMem = %d, randomAccess = %c",
			 enforceUnique ? 't' : 'f',
			 workMem, randomAccess ? 't' : 'f');
#endif

	state->nKeys = IndexRelationGetNumberOfKeyAttributes(indexRel);

	TRACE_POSTGRESQL_SORT_START(INDEX_SORT,
								enforceUnique,
								state->nKeys,
								workMem,
								randomAccess,
								PARALLEL_SORT(state));

	state->comparetup = comparetup_index_btree;
	state->copytup = copytup_index;
	state->writetup = writetup_index;
	state->readtup = readtup_index;
	state->abbrevNext = 10;

	state->heapRel = heapRel;
	state->indexRel = indexRel;
	state->enforceUnique = enforceUnique;

	indexScanKey = _bt_mkscankey(indexRel, NULL);

	/* Prepare SortSupport data for each column */
	state->sortKeys = (SortSupport) palloc0(state->nKeys *
											sizeof(SortSupportData));

	for (i = 0; i < state->nKeys; i++)
	{
		SortSupport sortKey = state->sortKeys + i;
		ScanKey		scanKey = indexScanKey->scankeys + i;
		int16		strategy;

		sortKey->ssup_cxt = CurrentMemoryContext;
		sortKey->ssup_collation = scanKey->sk_collation;
		sortKey->ssup_nulls_first =
			(scanKey->sk_flags & SK_BT_NULLS_FIRST) != 0;
		sortKey->ssup_attno = scanKey->sk_attno;
		/* Convey if abbreviation optimization is applicable in principle */
		sortKey->abbreviate = (i == 0);

		AssertState(sortKey->ssup_attno != 0);

		strategy = (scanKey->sk_flags & SK_BT_DESC) != 0 ?
			BTGreaterStrategyNumber : BTLessStrategyNumber;

		PrepareSortSupportFromIndexRel(indexRel, strategy, sortKey);
	}

	pfree(indexScanKey);

	MemoryContextSwitchTo(oldcontext);

	return state;
}