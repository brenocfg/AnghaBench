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
struct TYPE_5__ {int /*<<< orphan*/  const* tts_ops; } ;
struct TYPE_4__ {int resultopsfixed; TYPE_2__* ps_ResultTupleSlot; scalar_t__ resultopsset; int /*<<< orphan*/  const* resultops; } ;
typedef  TYPE_1__ PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  const TTSOpsVirtual ; 
 int TTS_FIXED (TYPE_2__*) ; 

const TupleTableSlotOps *
ExecGetResultSlotOps(PlanState *planstate, bool *isfixed)
{
	if (planstate->resultopsset && planstate->resultops)
	{
		if (isfixed)
			*isfixed = planstate->resultopsfixed;
		return planstate->resultops;
	}

	if (isfixed)
	{
		if (planstate->resultopsset)
			*isfixed = planstate->resultopsfixed;
		else if (planstate->ps_ResultTupleSlot)
			*isfixed = TTS_FIXED(planstate->ps_ResultTupleSlot);
		else
			*isfixed = false;
	}

	if (!planstate->ps_ResultTupleSlot)
		return &TTSOpsVirtual;

	return planstate->ps_ResultTupleSlot->tts_ops;
}