#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_4__ {scalar_t__ sort_out; int /*<<< orphan*/ * sort_slot; scalar_t__ sort_in; } ;
typedef  TYPE_1__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_1__*) ; 
 int /*<<< orphan*/  tuplesort_gettupleslot (scalar_t__,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplesort_puttupleslot (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
fetch_input_tuple(AggState *aggstate)
{
	TupleTableSlot *slot;

	if (aggstate->sort_in)
	{
		/* make sure we check for interrupts in either path through here */
		CHECK_FOR_INTERRUPTS();
		if (!tuplesort_gettupleslot(aggstate->sort_in, true, false,
									aggstate->sort_slot, NULL))
			return NULL;
		slot = aggstate->sort_slot;
	}
	else
		slot = ExecProcNode(outerPlanState(aggstate));

	if (!TupIsNull(slot) && aggstate->sort_out)
		tuplesort_puttupleslot(aggstate->sort_out, slot);

	return slot;
}