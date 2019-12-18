#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* ps_ExprContext; scalar_t__ plan; } ;
struct TYPE_11__ {int /*<<< orphan*/  ss_ScanTupleSlot; TYPE_2__ ps; } ;
struct TYPE_12__ {int grouptail_valid; int grouptailpos; int spooled_rows; int currentpos; int /*<<< orphan*/  temp_slot_2; TYPE_3__ ss; int /*<<< orphan*/  buffer; int /*<<< orphan*/  grouptail_ptr; } ;
typedef  TYPE_4__ WindowAggState ;
struct TYPE_13__ {scalar_t__ ordNumCols; } ;
typedef  TYPE_5__ WindowAgg ;
struct TYPE_9__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  are_peers (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spool_tuples (TYPE_4__*,int) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_grouptailpos(WindowAggState *winstate)
{
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	MemoryContext oldcontext;

	if (winstate->grouptail_valid)
		return;					/* already known for current row */

	/* We may be called in a short-lived context */
	oldcontext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_query_memory);

	/* If no ORDER BY, all rows are peers with each other */
	if (node->ordNumCols == 0)
	{
		spool_tuples(winstate, -1);
		winstate->grouptailpos = winstate->spooled_rows;
		winstate->grouptail_valid = true;
		MemoryContextSwitchTo(oldcontext);
		return;
	}

	/*
	 * Because grouptail_valid is reset only when current row advances into a
	 * new peer group, we always reach here knowing that grouptailpos needs to
	 * be advanced by at least one row.  Hence, unlike the otherwise similar
	 * case for frame tail tracking, we do not need persistent storage of the
	 * group tail row.
	 */
	Assert(winstate->grouptailpos <= winstate->currentpos);
	tuplestore_select_read_pointer(winstate->buffer,
								   winstate->grouptail_ptr);
	for (;;)
	{
		/* Note we advance grouptailpos even if the fetch fails */
		winstate->grouptailpos++;
		spool_tuples(winstate, winstate->grouptailpos);
		if (!tuplestore_gettupleslot(winstate->buffer, true, true,
									 winstate->temp_slot_2))
			break;				/* end of partition */
		if (winstate->grouptailpos > winstate->currentpos &&
			!are_peers(winstate, winstate->temp_slot_2,
					   winstate->ss.ss_ScanTupleSlot))
			break;				/* this row is the group tail */
	}
	ExecClearTuple(winstate->temp_slot_2);
	winstate->grouptail_valid = true;

	MemoryContextSwitchTo(oldcontext);
}