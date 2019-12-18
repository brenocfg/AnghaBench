#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nbatch; TYPE_2__* batches; int /*<<< orphan*/  area; int /*<<< orphan*/  hashCxt; TYPE_1__* parallel_state; } ;
struct TYPE_7__ {int done; void* outer_tuples; void* inner_tuples; scalar_t__ preallocated; int /*<<< orphan*/ * shared; } ;
struct TYPE_6__ {scalar_t__ nbatch; int /*<<< orphan*/  fileset; int /*<<< orphan*/  nparticipants; int /*<<< orphan*/  batches; } ;
typedef  TYPE_1__ ParallelHashJoinState ;
typedef  TYPE_2__ ParallelHashJoinBatchAccessor ;
typedef  int /*<<< orphan*/  ParallelHashJoinBatch ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecParallelHashCloseBatchAccessors (TYPE_3__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NthParallelHashJoinBatch (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ParallelHashJoinBatchInner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParallelHashJoinBatchOuter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ParallelWorkerNumber ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 void* sts_attach (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExecParallelHashEnsureBatchAccessors(HashJoinTable hashtable)
{
	ParallelHashJoinState *pstate = hashtable->parallel_state;
	ParallelHashJoinBatch *batches;
	MemoryContext oldcxt;
	int			i;

	if (hashtable->batches != NULL)
	{
		if (hashtable->nbatch == pstate->nbatch)
			return;
		ExecParallelHashCloseBatchAccessors(hashtable);
	}

	/*
	 * It's possible for a backend to start up very late so that the whole
	 * join is finished and the shm state for tracking batches has already
	 * been freed by ExecHashTableDetach().  In that case we'll just leave
	 * hashtable->batches as NULL so that ExecParallelHashJoinNewBatch() gives
	 * up early.
	 */
	if (!DsaPointerIsValid(pstate->batches))
		return;

	/* Use hash join memory context. */
	oldcxt = MemoryContextSwitchTo(hashtable->hashCxt);

	/* Allocate this backend's accessor array. */
	hashtable->nbatch = pstate->nbatch;
	hashtable->batches = (ParallelHashJoinBatchAccessor *)
		palloc0(sizeof(ParallelHashJoinBatchAccessor) * hashtable->nbatch);

	/* Find the base of the pseudo-array of ParallelHashJoinBatch objects. */
	batches = (ParallelHashJoinBatch *)
		dsa_get_address(hashtable->area, pstate->batches);

	/* Set up the accessor array and attach to the tuplestores. */
	for (i = 0; i < hashtable->nbatch; ++i)
	{
		ParallelHashJoinBatchAccessor *accessor = &hashtable->batches[i];
		ParallelHashJoinBatch *shared = NthParallelHashJoinBatch(batches, i);

		accessor->shared = shared;
		accessor->preallocated = 0;
		accessor->done = false;
		accessor->inner_tuples =
			sts_attach(ParallelHashJoinBatchInner(shared),
					   ParallelWorkerNumber + 1,
					   &pstate->fileset);
		accessor->outer_tuples =
			sts_attach(ParallelHashJoinBatchOuter(shared,
												  pstate->nparticipants),
					   ParallelWorkerNumber + 1,
					   &pstate->fileset);
	}

	MemoryContextSwitchTo(oldcxt);
}