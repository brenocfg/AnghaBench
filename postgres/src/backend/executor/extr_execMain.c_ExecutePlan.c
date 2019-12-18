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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {int /*<<< orphan*/  (* receiveSlot ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
struct TYPE_7__ {int es_use_parallel_mode; int es_top_eflags; int /*<<< orphan*/  es_processed; int /*<<< orphan*/ * es_junkFilter; int /*<<< orphan*/  es_direction; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_1__ EState ;
typedef  TYPE_2__ DestReceiver ;
typedef  scalar_t__ CmdType ;

/* Variables and functions */
 scalar_t__ CMD_SELECT ; 
 int EXEC_FLAG_BACKWARD ; 
 int /*<<< orphan*/  EnterParallelMode () ; 
 int /*<<< orphan*/ * ExecFilterJunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecShutdownNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExitParallelMode () ; 
 int /*<<< orphan*/  ResetPerTupleExprContext (TYPE_1__*) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
ExecutePlan(EState *estate,
			PlanState *planstate,
			bool use_parallel_mode,
			CmdType operation,
			bool sendTuples,
			uint64 numberTuples,
			ScanDirection direction,
			DestReceiver *dest,
			bool execute_once)
{
	TupleTableSlot *slot;
	uint64		current_tuple_count;

	/*
	 * initialize local variables
	 */
	current_tuple_count = 0;

	/*
	 * Set the direction.
	 */
	estate->es_direction = direction;

	/*
	 * If the plan might potentially be executed multiple times, we must force
	 * it to run without parallelism, because we might exit early.
	 */
	if (!execute_once)
		use_parallel_mode = false;

	estate->es_use_parallel_mode = use_parallel_mode;
	if (use_parallel_mode)
		EnterParallelMode();

	/*
	 * Loop until we've processed the proper number of tuples from the plan.
	 */
	for (;;)
	{
		/* Reset the per-output-tuple exprcontext */
		ResetPerTupleExprContext(estate);

		/*
		 * Execute the plan and obtain a tuple
		 */
		slot = ExecProcNode(planstate);

		/*
		 * if the tuple is null, then we assume there is nothing more to
		 * process so we just end the loop...
		 */
		if (TupIsNull(slot))
			break;

		/*
		 * If we have a junk filter, then project a new tuple with the junk
		 * removed.
		 *
		 * Store this new "clean" tuple in the junkfilter's resultSlot.
		 * (Formerly, we stored it back over the "dirty" tuple, which is WRONG
		 * because that tuple slot has the wrong descriptor.)
		 */
		if (estate->es_junkFilter != NULL)
			slot = ExecFilterJunk(estate->es_junkFilter, slot);

		/*
		 * If we are supposed to send the tuple somewhere, do so. (In
		 * practice, this is probably always the case at this point.)
		 */
		if (sendTuples)
		{
			/*
			 * If we are not able to send the tuple, we assume the destination
			 * has closed and no more tuples can be sent. If that's the case,
			 * end the loop.
			 */
			if (!dest->receiveSlot(slot, dest))
				break;
		}

		/*
		 * Count tuples processed, if this is a SELECT.  (For other operation
		 * types, the ModifyTable plan node must count the appropriate
		 * events.)
		 */
		if (operation == CMD_SELECT)
			(estate->es_processed)++;

		/*
		 * check our tuple count.. if we've processed the proper number then
		 * quit, else loop again and process more tuples.  Zero numberTuples
		 * means no limit.
		 */
		current_tuple_count++;
		if (numberTuples && numberTuples == current_tuple_count)
			break;
	}

	/*
	 * If we know we won't need to back up, we can release resources at this
	 * point.
	 */
	if (!(estate->es_top_eflags & EXEC_FLAG_BACKWARD))
		(void) ExecShutdownNode(planstate);

	if (use_parallel_mode)
		ExitParallelMode();
}