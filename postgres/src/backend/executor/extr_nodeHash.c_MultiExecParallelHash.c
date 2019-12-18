#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_22__ {int /*<<< orphan*/ * ecxt_outertuple; } ;
struct TYPE_21__ {int nbatch; int curbatch; int /*<<< orphan*/  totalTuples; int /*<<< orphan*/  nbuckets; int /*<<< orphan*/  log2_nbuckets; TYPE_2__* batches; int /*<<< orphan*/  partialTuples; int /*<<< orphan*/  keepNulls; TYPE_3__* parallel_state; } ;
struct TYPE_17__ {TYPE_6__* ps_ExprContext; } ;
struct TYPE_20__ {TYPE_1__ ps; int /*<<< orphan*/ * hashkeys; TYPE_5__* hashtable; } ;
struct TYPE_19__ {int /*<<< orphan*/  total_tuples; int /*<<< orphan*/  nbuckets; int /*<<< orphan*/  growth; int /*<<< orphan*/  grow_batches_barrier; int /*<<< orphan*/  grow_buckets_barrier; int /*<<< orphan*/  build_barrier; } ;
struct TYPE_18__ {int /*<<< orphan*/  inner_tuples; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_3__ ParallelHashJoinState ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ HashState ;
typedef  TYPE_5__* HashJoinTable ;
typedef  TYPE_6__ ExprContext ;
typedef  int /*<<< orphan*/  Barrier ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BarrierArriveAndWait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BarrierAttach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BarrierDetach (int /*<<< orphan*/ *) ; 
 int BarrierPhase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecHashGetHashValue (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecParallelHashEnsureBatchAccessors (TYPE_5__*) ; 
 int /*<<< orphan*/  ExecParallelHashIncreaseNumBatches (TYPE_5__*) ; 
 int /*<<< orphan*/  ExecParallelHashIncreaseNumBuckets (TYPE_5__*) ; 
 int /*<<< orphan*/  ExecParallelHashMergeCounters (TYPE_5__*) ; 
 int /*<<< orphan*/  ExecParallelHashTableInsert (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecParallelHashTableSetCurrentBatch (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
#define  PHJ_BUILD_ALLOCATING 129 
 int PHJ_BUILD_DONE ; 
#define  PHJ_BUILD_HASHING_INNER 128 
 int PHJ_BUILD_HASHING_OUTER ; 
 int /*<<< orphan*/  PHJ_GROWTH_DISABLED ; 
 int /*<<< orphan*/  PHJ_GROW_BATCHES_ELECTING ; 
 int /*<<< orphan*/  PHJ_GROW_BATCHES_PHASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHJ_GROW_BUCKETS_ELECTING ; 
 int /*<<< orphan*/  PHJ_GROW_BUCKETS_PHASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_EVENT_HASH_BUILD_ALLOCATING ; 
 int /*<<< orphan*/  WAIT_EVENT_HASH_BUILD_HASHING_INNER ; 
 int /*<<< orphan*/  my_log2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_4__*) ; 
 int /*<<< orphan*/  sts_end_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MultiExecParallelHash(HashState *node)
{
	ParallelHashJoinState *pstate;
	PlanState  *outerNode;
	List	   *hashkeys;
	HashJoinTable hashtable;
	TupleTableSlot *slot;
	ExprContext *econtext;
	uint32		hashvalue;
	Barrier    *build_barrier;
	int			i;

	/*
	 * get state info from node
	 */
	outerNode = outerPlanState(node);
	hashtable = node->hashtable;

	/*
	 * set expression context
	 */
	hashkeys = node->hashkeys;
	econtext = node->ps.ps_ExprContext;

	/*
	 * Synchronize the parallel hash table build.  At this stage we know that
	 * the shared hash table has been or is being set up by
	 * ExecHashTableCreate(), but we don't know if our peers have returned
	 * from there or are here in MultiExecParallelHash(), and if so how far
	 * through they are.  To find out, we check the build_barrier phase then
	 * and jump to the right step in the build algorithm.
	 */
	pstate = hashtable->parallel_state;
	build_barrier = &pstate->build_barrier;
	Assert(BarrierPhase(build_barrier) >= PHJ_BUILD_ALLOCATING);
	switch (BarrierPhase(build_barrier))
	{
		case PHJ_BUILD_ALLOCATING:

			/*
			 * Either I just allocated the initial hash table in
			 * ExecHashTableCreate(), or someone else is doing that.  Either
			 * way, wait for everyone to arrive here so we can proceed.
			 */
			BarrierArriveAndWait(build_barrier, WAIT_EVENT_HASH_BUILD_ALLOCATING);
			/* Fall through. */

		case PHJ_BUILD_HASHING_INNER:

			/*
			 * It's time to begin hashing, or if we just arrived here then
			 * hashing is already underway, so join in that effort.  While
			 * hashing we have to be prepared to help increase the number of
			 * batches or buckets at any time, and if we arrived here when
			 * that was already underway we'll have to help complete that work
			 * immediately so that it's safe to access batches and buckets
			 * below.
			 */
			if (PHJ_GROW_BATCHES_PHASE(BarrierAttach(&pstate->grow_batches_barrier)) !=
				PHJ_GROW_BATCHES_ELECTING)
				ExecParallelHashIncreaseNumBatches(hashtable);
			if (PHJ_GROW_BUCKETS_PHASE(BarrierAttach(&pstate->grow_buckets_barrier)) !=
				PHJ_GROW_BUCKETS_ELECTING)
				ExecParallelHashIncreaseNumBuckets(hashtable);
			ExecParallelHashEnsureBatchAccessors(hashtable);
			ExecParallelHashTableSetCurrentBatch(hashtable, 0);
			for (;;)
			{
				slot = ExecProcNode(outerNode);
				if (TupIsNull(slot))
					break;
				econtext->ecxt_outertuple = slot;
				if (ExecHashGetHashValue(hashtable, econtext, hashkeys,
										 false, hashtable->keepNulls,
										 &hashvalue))
					ExecParallelHashTableInsert(hashtable, slot, hashvalue);
				hashtable->partialTuples++;
			}

			/*
			 * Make sure that any tuples we wrote to disk are visible to
			 * others before anyone tries to load them.
			 */
			for (i = 0; i < hashtable->nbatch; ++i)
				sts_end_write(hashtable->batches[i].inner_tuples);

			/*
			 * Update shared counters.  We need an accurate total tuple count
			 * to control the empty table optimization.
			 */
			ExecParallelHashMergeCounters(hashtable);

			BarrierDetach(&pstate->grow_buckets_barrier);
			BarrierDetach(&pstate->grow_batches_barrier);

			/*
			 * Wait for everyone to finish building and flushing files and
			 * counters.
			 */
			if (BarrierArriveAndWait(build_barrier,
									 WAIT_EVENT_HASH_BUILD_HASHING_INNER))
			{
				/*
				 * Elect one backend to disable any further growth.  Batches
				 * are now fixed.  While building them we made sure they'd fit
				 * in our memory budget when we load them back in later (or we
				 * tried to do that and gave up because we detected extreme
				 * skew).
				 */
				pstate->growth = PHJ_GROWTH_DISABLED;
			}
	}

	/*
	 * We're not yet attached to a batch.  We all agree on the dimensions and
	 * number of inner tuples (for the empty table optimization).
	 */
	hashtable->curbatch = -1;
	hashtable->nbuckets = pstate->nbuckets;
	hashtable->log2_nbuckets = my_log2(hashtable->nbuckets);
	hashtable->totalTuples = pstate->total_tuples;
	ExecParallelHashEnsureBatchAccessors(hashtable);

	/*
	 * The next synchronization point is in ExecHashJoin's HJ_BUILD_HASHTABLE
	 * case, which will bring the build phase to PHJ_BUILD_DONE (if it isn't
	 * there already).
	 */
	Assert(BarrierPhase(build_barrier) == PHJ_BUILD_HASHING_OUTER ||
		   BarrierPhase(build_barrier) == PHJ_BUILD_DONE);
}