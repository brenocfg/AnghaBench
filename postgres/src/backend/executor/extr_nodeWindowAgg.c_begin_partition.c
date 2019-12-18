#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* WindowStatePerFunc ;
typedef  TYPE_4__* WindowObject ;
struct TYPE_9__ {scalar_t__ plan; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_13__ {int frameOptions; int numfuncs; int partition_spooled; int framehead_valid; int frametail_valid; int grouptail_valid; int grouptailpos; int more_partitions; scalar_t__ numaggs; int framehead_ptr; int frametail_ptr; int grouptail_ptr; scalar_t__ spooled_rows; int /*<<< orphan*/ * first_part_slot; int /*<<< orphan*/  buffer; TYPE_3__* perfunc; scalar_t__ aggregatedupto; scalar_t__ aggregatedbase; TYPE_4__* agg_winobj; scalar_t__ current_ptr; scalar_t__ frametail_slot; scalar_t__ framehead_slot; scalar_t__ agg_row_slot; scalar_t__ groupheadpos; scalar_t__ frametailgroup; scalar_t__ frameheadgroup; scalar_t__ currentgroup; scalar_t__ frametailpos; scalar_t__ frameheadpos; scalar_t__ currentpos; TYPE_2__ ss; } ;
typedef  TYPE_5__ WindowAggState ;
struct TYPE_14__ {scalar_t__ ordNumCols; } ;
typedef  TYPE_6__ WindowAgg ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_12__ {int markpos; int seekpos; void* readptr; void* markptr; } ;
struct TYPE_11__ {TYPE_4__* winobj; int /*<<< orphan*/  plain_agg; } ;
typedef  int /*<<< orphan*/  PlanState ;

/* Variables and functions */
 int EXEC_FLAG_BACKWARD ; 
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
 int FRAMEOPTION_END_CURRENT_ROW ; 
 int FRAMEOPTION_END_OFFSET ; 
 int FRAMEOPTION_EXCLUDE_GROUP ; 
 int FRAMEOPTION_EXCLUDE_TIES ; 
 int FRAMEOPTION_EXCLUSION ; 
 int FRAMEOPTION_GROUPS ; 
 int FRAMEOPTION_RANGE ; 
 int FRAMEOPTION_START_CURRENT_ROW ; 
 int FRAMEOPTION_START_OFFSET ; 
 int FRAMEOPTION_START_UNBOUNDED_PRECEDING ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_5__*) ; 
 void* tuplestore_alloc_read_pointer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttupleslot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_set_eflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
begin_partition(WindowAggState *winstate)
{
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	PlanState  *outerPlan = outerPlanState(winstate);
	int			frameOptions = winstate->frameOptions;
	int			numfuncs = winstate->numfuncs;
	int			i;

	winstate->partition_spooled = false;
	winstate->framehead_valid = false;
	winstate->frametail_valid = false;
	winstate->grouptail_valid = false;
	winstate->spooled_rows = 0;
	winstate->currentpos = 0;
	winstate->frameheadpos = 0;
	winstate->frametailpos = 0;
	winstate->currentgroup = 0;
	winstate->frameheadgroup = 0;
	winstate->frametailgroup = 0;
	winstate->groupheadpos = 0;
	winstate->grouptailpos = -1;	/* see update_grouptailpos */
	ExecClearTuple(winstate->agg_row_slot);
	if (winstate->framehead_slot)
		ExecClearTuple(winstate->framehead_slot);
	if (winstate->frametail_slot)
		ExecClearTuple(winstate->frametail_slot);

	/*
	 * If this is the very first partition, we need to fetch the first input
	 * row to store in first_part_slot.
	 */
	if (TupIsNull(winstate->first_part_slot))
	{
		TupleTableSlot *outerslot = ExecProcNode(outerPlan);

		if (!TupIsNull(outerslot))
			ExecCopySlot(winstate->first_part_slot, outerslot);
		else
		{
			/* outer plan is empty, so we have nothing to do */
			winstate->partition_spooled = true;
			winstate->more_partitions = false;
			return;
		}
	}

	/* Create new tuplestore for this partition */
	winstate->buffer = tuplestore_begin_heap(false, false, work_mem);

	/*
	 * Set up read pointers for the tuplestore.  The current pointer doesn't
	 * need BACKWARD capability, but the per-window-function read pointers do,
	 * and the aggregate pointer does if we might need to restart aggregation.
	 */
	winstate->current_ptr = 0;	/* read pointer 0 is pre-allocated */

	/* reset default REWIND capability bit for current ptr */
	tuplestore_set_eflags(winstate->buffer, 0);

	/* create read pointers for aggregates, if needed */
	if (winstate->numaggs > 0)
	{
		WindowObject agg_winobj = winstate->agg_winobj;
		int			readptr_flags = 0;

		/*
		 * If the frame head is potentially movable, or we have an EXCLUSION
		 * clause, we might need to restart aggregation ...
		 */
		if (!(frameOptions & FRAMEOPTION_START_UNBOUNDED_PRECEDING) ||
			(frameOptions & FRAMEOPTION_EXCLUSION))
		{
			/* ... so create a mark pointer to track the frame head */
			agg_winobj->markptr = tuplestore_alloc_read_pointer(winstate->buffer, 0);
			/* and the read pointer will need BACKWARD capability */
			readptr_flags |= EXEC_FLAG_BACKWARD;
		}

		agg_winobj->readptr = tuplestore_alloc_read_pointer(winstate->buffer,
															readptr_flags);
		agg_winobj->markpos = -1;
		agg_winobj->seekpos = -1;

		/* Also reset the row counters for aggregates */
		winstate->aggregatedbase = 0;
		winstate->aggregatedupto = 0;
	}

	/* create mark and read pointers for each real window function */
	for (i = 0; i < numfuncs; i++)
	{
		WindowStatePerFunc perfuncstate = &(winstate->perfunc[i]);

		if (!perfuncstate->plain_agg)
		{
			WindowObject winobj = perfuncstate->winobj;

			winobj->markptr = tuplestore_alloc_read_pointer(winstate->buffer,
															0);
			winobj->readptr = tuplestore_alloc_read_pointer(winstate->buffer,
															EXEC_FLAG_BACKWARD);
			winobj->markpos = -1;
			winobj->seekpos = -1;
		}
	}

	/*
	 * If we are in RANGE or GROUPS mode, then determining frame boundaries
	 * requires physical access to the frame endpoint rows, except in certain
	 * degenerate cases.  We create read pointers to point to those rows, to
	 * simplify access and ensure that the tuplestore doesn't discard the
	 * endpoint rows prematurely.  (Must create pointers in exactly the same
	 * cases that update_frameheadpos and update_frametailpos need them.)
	 */
	winstate->framehead_ptr = winstate->frametail_ptr = -1; /* if not used */

	if (frameOptions & (FRAMEOPTION_RANGE | FRAMEOPTION_GROUPS))
	{
		if (((frameOptions & FRAMEOPTION_START_CURRENT_ROW) &&
			 node->ordNumCols != 0) ||
			(frameOptions & FRAMEOPTION_START_OFFSET))
			winstate->framehead_ptr =
				tuplestore_alloc_read_pointer(winstate->buffer, 0);
		if (((frameOptions & FRAMEOPTION_END_CURRENT_ROW) &&
			 node->ordNumCols != 0) ||
			(frameOptions & FRAMEOPTION_END_OFFSET))
			winstate->frametail_ptr =
				tuplestore_alloc_read_pointer(winstate->buffer, 0);
	}

	/*
	 * If we have an exclusion clause that requires knowing the boundaries of
	 * the current row's peer group, we create a read pointer to track the
	 * tail position of the peer group (i.e., first row of the next peer
	 * group).  The head position does not require its own pointer because we
	 * maintain that as a side effect of advancing the current row.
	 */
	winstate->grouptail_ptr = -1;

	if ((frameOptions & (FRAMEOPTION_EXCLUDE_GROUP |
						 FRAMEOPTION_EXCLUDE_TIES)) &&
		node->ordNumCols != 0)
	{
		winstate->grouptail_ptr =
			tuplestore_alloc_read_pointer(winstate->buffer, 0);
	}

	/*
	 * Store the first tuple into the tuplestore (it's always available now;
	 * we either read it above, or saved it at the end of previous partition)
	 */
	tuplestore_puttupleslot(winstate->buffer, winstate->first_part_slot);
	winstate->spooled_rows++;
}