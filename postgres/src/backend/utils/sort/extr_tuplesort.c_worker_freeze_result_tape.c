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
struct TYPE_5__ {int result_tape; scalar_t__ memtupcount; size_t worker; int /*<<< orphan*/  tapeset; scalar_t__ memtupsize; int /*<<< orphan*/ * memtuples; TYPE_2__* shared; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  TapeShare ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  workersFinished; int /*<<< orphan*/ * tapes; } ;
typedef  TYPE_2__ Sharedsort ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LogicalTapeFreeze (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int WORKER (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
worker_freeze_result_tape(Tuplesortstate *state)
{
	Sharedsort *shared = state->shared;
	TapeShare	output;

	Assert(WORKER(state));
	Assert(state->result_tape != -1);
	Assert(state->memtupcount == 0);

	/*
	 * Free most remaining memory, in case caller is sensitive to our holding
	 * on to it.  memtuples may not be a tiny merge heap at this point.
	 */
	pfree(state->memtuples);
	/* Be tidy */
	state->memtuples = NULL;
	state->memtupsize = 0;

	/*
	 * Parallel worker requires result tape metadata, which is to be stored in
	 * shared memory for leader
	 */
	LogicalTapeFreeze(state->tapeset, state->result_tape, &output);

	/* Store properties of output tape, and update finished worker count */
	SpinLockAcquire(&shared->mutex);
	shared->tapes[state->worker] = output;
	shared->workersFinished++;
	SpinLockRelease(&shared->mutex);
}