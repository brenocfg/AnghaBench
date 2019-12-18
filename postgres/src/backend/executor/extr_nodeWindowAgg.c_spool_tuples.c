#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_11__ {TYPE_1__* ps_ExprContext; scalar_t__ plan; } ;
struct TYPE_12__ {TYPE_2__ ps; } ;
struct TYPE_13__ {int partition_spooled; int spooled_rows; int more_partitions; int /*<<< orphan*/  buffer; int /*<<< orphan*/  first_part_slot; int /*<<< orphan*/  partEqfunction; TYPE_6__* tmpcontext; TYPE_3__ ss; } ;
typedef  TYPE_4__ WindowAggState ;
struct TYPE_14__ {scalar_t__ partNumCols; } ;
typedef  TYPE_5__ WindowAgg ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_15__ {int /*<<< orphan*/ * ecxt_outertuple; int /*<<< orphan*/  ecxt_innertuple; } ;
struct TYPE_10__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_6__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecQualAndReset (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_4__*) ; 
 int /*<<< orphan*/  tuplestore_in_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttupleslot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spool_tuples(WindowAggState *winstate, int64 pos)
{
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	PlanState  *outerPlan;
	TupleTableSlot *outerslot;
	MemoryContext oldcontext;

	if (!winstate->buffer)
		return;					/* just a safety check */
	if (winstate->partition_spooled)
		return;					/* whole partition done already */

	/*
	 * If the tuplestore has spilled to disk, alternate reading and writing
	 * becomes quite expensive due to frequent buffer flushes.  It's cheaper
	 * to force the entire partition to get spooled in one go.
	 *
	 * XXX this is a horrid kluge --- it'd be better to fix the performance
	 * problem inside tuplestore.  FIXME
	 */
	if (!tuplestore_in_memory(winstate->buffer))
		pos = -1;

	outerPlan = outerPlanState(winstate);

	/* Must be in query context to call outerplan */
	oldcontext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_query_memory);

	while (winstate->spooled_rows <= pos || pos == -1)
	{
		outerslot = ExecProcNode(outerPlan);
		if (TupIsNull(outerslot))
		{
			/* reached the end of the last partition */
			winstate->partition_spooled = true;
			winstate->more_partitions = false;
			break;
		}

		if (node->partNumCols > 0)
		{
			ExprContext *econtext = winstate->tmpcontext;

			econtext->ecxt_innertuple = winstate->first_part_slot;
			econtext->ecxt_outertuple = outerslot;

			/* Check if this tuple still belongs to the current partition */
			if (!ExecQualAndReset(winstate->partEqfunction, econtext))
			{
				/*
				 * end of partition; copy the tuple for the next cycle.
				 */
				ExecCopySlot(winstate->first_part_slot, outerslot);
				winstate->partition_spooled = true;
				winstate->more_partitions = true;
				break;
			}
		}

		/* Still in partition, so save it into the tuplestore */
		tuplestore_puttupleslot(winstate->buffer, outerslot);
		winstate->spooled_rows++;
	}

	MemoryContextSwitchTo(oldcontext);
}