#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlotOps ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_5__ {int resultopsset; int /*<<< orphan*/  const* resultops; int /*<<< orphan*/ * ps_ResultTupleDesc; int /*<<< orphan*/  resultopsfixed; int /*<<< orphan*/ * ps_ResultTupleSlot; TYPE_1__* state; } ;
struct TYPE_4__ {int /*<<< orphan*/  es_tupleTable; } ;
typedef  TYPE_2__ PlanState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecAllocTableSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
ExecInitResultSlot(PlanState *planstate, const TupleTableSlotOps *tts_ops)
{
	TupleTableSlot *slot;

	slot = ExecAllocTableSlot(&planstate->state->es_tupleTable,
							  planstate->ps_ResultTupleDesc, tts_ops);
	planstate->ps_ResultTupleSlot = slot;

	planstate->resultopsfixed = planstate->ps_ResultTupleDesc != NULL;
	planstate->resultops = tts_ops;
	planstate->resultopsset = true;
}