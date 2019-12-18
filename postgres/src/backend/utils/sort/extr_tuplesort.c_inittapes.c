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
struct TYPE_8__ {int* tp_fib; int* tp_dummy; int* tp_tapenum; size_t tapeRange; int Level; int /*<<< orphan*/  status; scalar_t__ destTape; scalar_t__* tp_runs; scalar_t__ currentRun; int /*<<< orphan*/  worker; TYPE_1__* shared; int /*<<< orphan*/  tapeset; int /*<<< orphan*/  ru_start; int /*<<< orphan*/  allowedMem; } ;
typedef  TYPE_2__ Tuplesortstate ;
struct TYPE_7__ {int /*<<< orphan*/  fileset; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LEADER (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LogicalTapeSetCreate (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MINORDER ; 
 int /*<<< orphan*/  TSS_BUILDRUNS ; 
 int WORKER (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inittapestate (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pg_rusage_show (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_sort ; 
 int tuplesort_merge_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
inittapes(Tuplesortstate *state, bool mergeruns)
{
	int			maxTapes,
				j;

	Assert(!LEADER(state));

	if (mergeruns)
	{
		/* Compute number of tapes to use: merge order plus 1 */
		maxTapes = tuplesort_merge_order(state->allowedMem) + 1;
	}
	else
	{
		/* Workers can sometimes produce single run, output without merge */
		Assert(WORKER(state));
		maxTapes = MINORDER + 1;
	}

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG, "worker %d switching to external sort with %d tapes: %s",
			 state->worker, maxTapes, pg_rusage_show(&state->ru_start));
#endif

	/* Create the tape set and allocate the per-tape data arrays */
	inittapestate(state, maxTapes);
	state->tapeset =
		LogicalTapeSetCreate(maxTapes, NULL,
							 state->shared ? &state->shared->fileset : NULL,
							 state->worker);

	state->currentRun = 0;

	/*
	 * Initialize variables of Algorithm D (step D1).
	 */
	for (j = 0; j < maxTapes; j++)
	{
		state->tp_fib[j] = 1;
		state->tp_runs[j] = 0;
		state->tp_dummy[j] = 1;
		state->tp_tapenum[j] = j;
	}
	state->tp_fib[state->tapeRange] = 0;
	state->tp_dummy[state->tapeRange] = 0;

	state->Level = 1;
	state->destTape = 0;

	state->status = TSS_BUILDRUNS;
}