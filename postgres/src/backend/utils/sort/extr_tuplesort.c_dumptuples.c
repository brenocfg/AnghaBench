#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int memtupcount; int memtupsize; scalar_t__ status; scalar_t__ currentRun; size_t destTape; int /*<<< orphan*/  ru_start; int /*<<< orphan*/  worker; int /*<<< orphan*/ * tp_dummy; int /*<<< orphan*/ * tp_runs; int /*<<< orphan*/ * tp_tapenum; int /*<<< orphan*/  tuplecontext; int /*<<< orphan*/ * memtuples; } ;
typedef  TYPE_1__ Tuplesortstate ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  LACKMEM (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 scalar_t__ TSS_BUILDRUNS ; 
 int /*<<< orphan*/  WRITETUP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,size_t,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 int /*<<< orphan*/  markrunend (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_rusage_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selectnewtape (TYPE_1__*) ; 
 scalar_t__ trace_sort ; 
 int /*<<< orphan*/  tuplesort_sort_memtuples (TYPE_1__*) ; 

__attribute__((used)) static void
dumptuples(Tuplesortstate *state, bool alltuples)
{
	int			memtupwrite;
	int			i;

	/*
	 * Nothing to do if we still fit in available memory and have array slots,
	 * unless this is the final call during initial run generation.
	 */
	if (state->memtupcount < state->memtupsize && !LACKMEM(state) &&
		!alltuples)
		return;

	/*
	 * Final call might require no sorting, in rare cases where we just so
	 * happen to have previously LACKMEM()'d at the point where exactly all
	 * remaining tuples are loaded into memory, just before input was
	 * exhausted.
	 *
	 * In general, short final runs are quite possible.  Rather than allowing
	 * a special case where there was a superfluous selectnewtape() call (i.e.
	 * a call with no subsequent run actually written to destTape), we prefer
	 * to write out a 0 tuple run.
	 *
	 * mergereadnext() is prepared for 0 tuple runs, and will reliably mark
	 * the tape inactive for the merge when called from beginmerge().  This
	 * case is therefore similar to the case where mergeonerun() finds a dummy
	 * run for the tape, and so doesn't need to merge a run from the tape (or
	 * conceptually "merges" the dummy run, if you prefer).  According to
	 * Knuth, Algorithm D "isn't strictly optimal" in its method of
	 * distribution and dummy run assignment; this edge case seems very
	 * unlikely to make that appreciably worse.
	 */
	Assert(state->status == TSS_BUILDRUNS);

	/*
	 * It seems unlikely that this limit will ever be exceeded, but take no
	 * chances
	 */
	if (state->currentRun == INT_MAX)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("cannot have more than %d runs for an external sort",
						INT_MAX)));

	state->currentRun++;

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG, "worker %d starting quicksort of run %d: %s",
			 state->worker, state->currentRun,
			 pg_rusage_show(&state->ru_start));
#endif

	/*
	 * Sort all tuples accumulated within the allowed amount of memory for
	 * this run using quicksort
	 */
	tuplesort_sort_memtuples(state);

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG, "worker %d finished quicksort of run %d: %s",
			 state->worker, state->currentRun,
			 pg_rusage_show(&state->ru_start));
#endif

	memtupwrite = state->memtupcount;
	for (i = 0; i < memtupwrite; i++)
	{
		WRITETUP(state, state->tp_tapenum[state->destTape],
				 &state->memtuples[i]);
		state->memtupcount--;
	}

	/*
	 * Reset tuple memory.  We've freed all of the tuples that we previously
	 * allocated.  It's important to avoid fragmentation when there is a stark
	 * change in the sizes of incoming tuples.  Fragmentation due to
	 * AllocSetFree's bucketing by size class might be particularly bad if
	 * this step wasn't taken.
	 */
	MemoryContextReset(state->tuplecontext);

	markrunend(state, state->tp_tapenum[state->destTape]);
	state->tp_runs[state->destTape]++;
	state->tp_dummy[state->destTape]--; /* per Alg D step D2 */

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG, "worker %d finished writing run %d to tape %d: %s",
			 state->worker, state->currentRun, state->destTape,
			 pg_rusage_show(&state->ru_start));
#endif

	if (!alltuples)
		selectnewtape(state);
}