#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nbatch; TYPE_3__* batches; TYPE_2__* parallel_state; } ;
struct TYPE_8__ {TYPE_1__* shared; scalar_t__ old_ntuples; scalar_t__ ntuples; scalar_t__ estimated_size; scalar_t__ size; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; scalar_t__ total_tuples; } ;
struct TYPE_6__ {scalar_t__ ntuples; int /*<<< orphan*/  old_ntuples; int /*<<< orphan*/  estimated_size; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ ParallelHashJoinState ;
typedef  TYPE_3__ ParallelHashJoinBatchAccessor ;
typedef  TYPE_4__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 

__attribute__((used)) static void
ExecParallelHashMergeCounters(HashJoinTable hashtable)
{
	ParallelHashJoinState *pstate = hashtable->parallel_state;
	int			i;

	LWLockAcquire(&pstate->lock, LW_EXCLUSIVE);
	pstate->total_tuples = 0;
	for (i = 0; i < hashtable->nbatch; ++i)
	{
		ParallelHashJoinBatchAccessor *batch = &hashtable->batches[i];

		batch->shared->size += batch->size;
		batch->shared->estimated_size += batch->estimated_size;
		batch->shared->ntuples += batch->ntuples;
		batch->shared->old_ntuples += batch->old_ntuples;
		batch->size = 0;
		batch->estimated_size = 0;
		batch->ntuples = 0;
		batch->old_ntuples = 0;
		pstate->total_tuples += batch->shared->ntuples;
	}
	LWLockRelease(&pstate->lock);
}