#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_14__ {int /*<<< orphan*/ * es_query_dsa; } ;
struct TYPE_13__ {scalar_t__ nTuples; scalar_t__ readCounter; scalar_t__ done; int /*<<< orphan*/ * tuple; } ;
struct TYPE_10__ {TYPE_5__* state; } ;
struct TYPE_12__ {int need_to_scan_locally; int /*<<< orphan*/ ** gm_slots; TYPE_4__* gm_tuple_buffers; TYPE_2__* pei; TYPE_1__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/ * area; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ GatherMergeState ;
typedef  TYPE_4__ GMReaderTupleBuffer ;
typedef  TYPE_5__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecStoreHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gm_readnext_tuple (TYPE_3__*,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  load_tuple_array (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_3__*) ; 

__attribute__((used)) static bool
gather_merge_readnext(GatherMergeState *gm_state, int reader, bool nowait)
{
	GMReaderTupleBuffer *tuple_buffer;
	HeapTuple	tup;

	/*
	 * If we're being asked to generate a tuple from the leader, then we just
	 * call ExecProcNode as normal to produce one.
	 */
	if (reader == 0)
	{
		if (gm_state->need_to_scan_locally)
		{
			PlanState  *outerPlan = outerPlanState(gm_state);
			TupleTableSlot *outerTupleSlot;
			EState	   *estate = gm_state->ps.state;

			/* Install our DSA area while executing the plan. */
			estate->es_query_dsa = gm_state->pei ? gm_state->pei->area : NULL;
			outerTupleSlot = ExecProcNode(outerPlan);
			estate->es_query_dsa = NULL;

			if (!TupIsNull(outerTupleSlot))
			{
				gm_state->gm_slots[0] = outerTupleSlot;
				return true;
			}
			/* need_to_scan_locally serves as "done" flag for leader */
			gm_state->need_to_scan_locally = false;
		}
		return false;
	}

	/* Otherwise, check the state of the relevant tuple buffer. */
	tuple_buffer = &gm_state->gm_tuple_buffers[reader - 1];

	if (tuple_buffer->nTuples > tuple_buffer->readCounter)
	{
		/* Return any tuple previously read that is still buffered. */
		tup = tuple_buffer->tuple[tuple_buffer->readCounter++];
	}
	else if (tuple_buffer->done)
	{
		/* Reader is known to be exhausted. */
		return false;
	}
	else
	{
		/* Read and buffer next tuple. */
		tup = gm_readnext_tuple(gm_state,
								reader,
								nowait,
								&tuple_buffer->done);
		if (!HeapTupleIsValid(tup))
			return false;

		/*
		 * Attempt to read more tuples in nowait mode and store them in the
		 * pending-tuple array for the reader.
		 */
		load_tuple_array(gm_state, reader);
	}

	Assert(HeapTupleIsValid(tup));

	/* Build the TupleTableSlot for the given tuple */
	ExecStoreHeapTuple(tup,		/* tuple to store */
					   gm_state->gm_slots[reader],	/* slot in which to store
													 * the tuple */
					   true);	/* pfree tuple when done with it */

	return true;
}