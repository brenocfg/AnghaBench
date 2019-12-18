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
struct TYPE_7__ {int nKeys; int abbrevNext; TYPE_2__* sortKeys; TYPE_2__* onlyKey; int /*<<< orphan*/  tupDesc; int /*<<< orphan*/  readtup; int /*<<< orphan*/  writetup; int /*<<< orphan*/  copytup; int /*<<< orphan*/  comparetup; int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_8__ {int ssup_nulls_first; int abbreviate; int /*<<< orphan*/  abbrev_converter; scalar_t__ ssup_attno; scalar_t__ ssup_collation; int /*<<< orphan*/  ssup_cxt; } ;
typedef  int /*<<< orphan*/  SortSupportData ;
typedef  TYPE_2__* SortSupport ;
typedef  int /*<<< orphan*/  SortCoordinate ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  HEAP_SORT ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARALLEL_SORT (TYPE_1__*) ; 
 int /*<<< orphan*/  PrepareSortSupportFromOrderingOp (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SORT_START (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comparetup_heap ; 
 int /*<<< orphan*/  copytup_heap ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int,char) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  readtup_heap ; 
 scalar_t__ trace_sort ; 
 TYPE_1__* tuplesort_begin_common (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writetup_heap ; 

Tuplesortstate *
tuplesort_begin_heap(TupleDesc tupDesc,
					 int nkeys, AttrNumber *attNums,
					 Oid *sortOperators, Oid *sortCollations,
					 bool *nullsFirstFlags,
					 int workMem, SortCoordinate coordinate, bool randomAccess)
{
	Tuplesortstate *state = tuplesort_begin_common(workMem, coordinate,
												   randomAccess);
	MemoryContext oldcontext;
	int			i;

	oldcontext = MemoryContextSwitchTo(state->sortcontext);

	AssertArg(nkeys > 0);

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG,
			 "begin tuple sort: nkeys = %d, workMem = %d, randomAccess = %c",
			 nkeys, workMem, randomAccess ? 't' : 'f');
#endif

	state->nKeys = nkeys;

	TRACE_POSTGRESQL_SORT_START(HEAP_SORT,
								false,	/* no unique check */
								nkeys,
								workMem,
								randomAccess,
								PARALLEL_SORT(state));

	state->comparetup = comparetup_heap;
	state->copytup = copytup_heap;
	state->writetup = writetup_heap;
	state->readtup = readtup_heap;

	state->tupDesc = tupDesc;	/* assume we need not copy tupDesc */
	state->abbrevNext = 10;

	/* Prepare SortSupport data for each column */
	state->sortKeys = (SortSupport) palloc0(nkeys * sizeof(SortSupportData));

	for (i = 0; i < nkeys; i++)
	{
		SortSupport sortKey = state->sortKeys + i;

		AssertArg(attNums[i] != 0);
		AssertArg(sortOperators[i] != 0);

		sortKey->ssup_cxt = CurrentMemoryContext;
		sortKey->ssup_collation = sortCollations[i];
		sortKey->ssup_nulls_first = nullsFirstFlags[i];
		sortKey->ssup_attno = attNums[i];
		/* Convey if abbreviation optimization is applicable in principle */
		sortKey->abbreviate = (i == 0);

		PrepareSortSupportFromOrderingOp(sortOperators[i], sortKey);
	}

	/*
	 * The "onlyKey" optimization cannot be used with abbreviated keys, since
	 * tie-breaker comparisons may be required.  Typically, the optimization
	 * is only of value to pass-by-value types anyway, whereas abbreviated
	 * keys are typically only of value to pass-by-reference types.
	 */
	if (nkeys == 1 && !state->sortKeys->abbrev_converter)
		state->onlyKey = state->sortKeys;

	MemoryContextSwitchTo(oldcontext);

	return state;
}