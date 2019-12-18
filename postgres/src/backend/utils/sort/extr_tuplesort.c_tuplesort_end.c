#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int allowedMem; int availMem; int /*<<< orphan*/  sortcontext; int /*<<< orphan*/ * estate; int /*<<< orphan*/ * tapeset; int /*<<< orphan*/  ru_start; int /*<<< orphan*/  worker; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_7__ {int /*<<< orphan*/  ecxt_scantuple; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 TYPE_2__* GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 long LogicalTapeSetBlocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogicalTapeSetClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ SERIAL (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SORT_DONE (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_rusage_show (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_sort ; 

void
tuplesort_end(Tuplesortstate *state)
{
	/* context swap probably not needed, but let's be safe */
	MemoryContext oldcontext = MemoryContextSwitchTo(state->sortcontext);

#ifdef TRACE_SORT
	long		spaceUsed;

	if (state->tapeset)
		spaceUsed = LogicalTapeSetBlocks(state->tapeset);
	else
		spaceUsed = (state->allowedMem - state->availMem + 1023) / 1024;
#endif

	/*
	 * Delete temporary "tape" files, if any.
	 *
	 * Note: want to include this in reported total cost of sort, hence need
	 * for two #ifdef TRACE_SORT sections.
	 */
	if (state->tapeset)
		LogicalTapeSetClose(state->tapeset);

#ifdef TRACE_SORT
	if (trace_sort)
	{
		if (state->tapeset)
			elog(LOG, "%s of worker %d ended, %ld disk blocks used: %s",
				 SERIAL(state) ? "external sort" : "parallel external sort",
				 state->worker, spaceUsed, pg_rusage_show(&state->ru_start));
		else
			elog(LOG, "%s of worker %d ended, %ld KB used: %s",
				 SERIAL(state) ? "internal sort" : "unperformed parallel sort",
				 state->worker, spaceUsed, pg_rusage_show(&state->ru_start));
	}

	TRACE_POSTGRESQL_SORT_DONE(state->tapeset != NULL, spaceUsed);
#else

	/*
	 * If you disabled TRACE_SORT, you can still probe sort__done, but you
	 * ain't getting space-used stats.
	 */
	TRACE_POSTGRESQL_SORT_DONE(state->tapeset != NULL, 0L);
#endif

	/* Free any execution state created for CLUSTER case */
	if (state->estate != NULL)
	{
		ExprContext *econtext = GetPerTupleExprContext(state->estate);

		ExecDropSingleTupleTableSlot(econtext->ecxt_scantuple);
		FreeExecutorState(state->estate);
	}

	MemoryContextSwitchTo(oldcontext);

	/*
	 * Free the per-sort memory context, thereby releasing all working memory,
	 * including the Tuplesortstate struct itself.
	 */
	MemoryContextDelete(state->sortcontext);
}