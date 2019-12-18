#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_11__ {int /*<<< orphan*/ * ecxt_innertuple; int /*<<< orphan*/ * ecxt_outertuple; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ps_ResultTupleSlot; TYPE_3__* ps_ExprContext; } ;
struct TYPE_10__ {int setop_done; scalar_t__ numOutput; int /*<<< orphan*/ * grp_firstTuple; int /*<<< orphan*/  eqfunction; TYPE_1__ ps; scalar_t__ pergroup; } ;
typedef  scalar_t__ SetOpStatePerGroup ;
typedef  TYPE_2__ SetOpState ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_3__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 void* ExecCopySlotHeapTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ExecStoreHeapTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  advance_counts (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_tuple_flag (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_counts (scalar_t__) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_2__*) ; 
 int /*<<< orphan*/  set_output_count (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static TupleTableSlot *
setop_retrieve_direct(SetOpState *setopstate)
{
	PlanState  *outerPlan;
	SetOpStatePerGroup pergroup;
	TupleTableSlot *outerslot;
	TupleTableSlot *resultTupleSlot;
	ExprContext *econtext = setopstate->ps.ps_ExprContext;

	/*
	 * get state info from node
	 */
	outerPlan = outerPlanState(setopstate);
	pergroup = (SetOpStatePerGroup) setopstate->pergroup;
	resultTupleSlot = setopstate->ps.ps_ResultTupleSlot;

	/*
	 * We loop retrieving groups until we find one we should return
	 */
	while (!setopstate->setop_done)
	{
		/*
		 * If we don't already have the first tuple of the new group, fetch it
		 * from the outer plan.
		 */
		if (setopstate->grp_firstTuple == NULL)
		{
			outerslot = ExecProcNode(outerPlan);
			if (!TupIsNull(outerslot))
			{
				/* Make a copy of the first input tuple */
				setopstate->grp_firstTuple = ExecCopySlotHeapTuple(outerslot);
			}
			else
			{
				/* outer plan produced no tuples at all */
				setopstate->setop_done = true;
				return NULL;
			}
		}

		/*
		 * Store the copied first input tuple in the tuple table slot reserved
		 * for it.  The tuple will be deleted when it is cleared from the
		 * slot.
		 */
		ExecStoreHeapTuple(setopstate->grp_firstTuple,
						   resultTupleSlot,
						   true);
		setopstate->grp_firstTuple = NULL;	/* don't keep two pointers */

		/* Initialize working state for a new input tuple group */
		initialize_counts(pergroup);

		/* Count the first input tuple */
		advance_counts(pergroup,
					   fetch_tuple_flag(setopstate, resultTupleSlot));

		/*
		 * Scan the outer plan until we exhaust it or cross a group boundary.
		 */
		for (;;)
		{
			outerslot = ExecProcNode(outerPlan);
			if (TupIsNull(outerslot))
			{
				/* no more outer-plan tuples available */
				setopstate->setop_done = true;
				break;
			}

			/*
			 * Check whether we've crossed a group boundary.
			 */
			econtext->ecxt_outertuple = resultTupleSlot;
			econtext->ecxt_innertuple = outerslot;

			if (!ExecQualAndReset(setopstate->eqfunction, econtext))
			{
				/*
				 * Save the first input tuple of the next group.
				 */
				setopstate->grp_firstTuple = ExecCopySlotHeapTuple(outerslot);
				break;
			}

			/* Still in same group, so count this tuple */
			advance_counts(pergroup,
						   fetch_tuple_flag(setopstate, outerslot));
		}

		/*
		 * Done scanning input tuple group.  See if we should emit any copies
		 * of result tuple, and if so return the first copy.
		 */
		set_output_count(setopstate, pergroup);

		if (setopstate->numOutput > 0)
		{
			setopstate->numOutput--;
			return resultTupleSlot;
		}
	}

	/* No more groups */
	ExecClearTuple(resultTupleSlot);
	return NULL;
}