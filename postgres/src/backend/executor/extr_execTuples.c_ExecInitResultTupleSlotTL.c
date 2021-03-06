#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlotOps ;
typedef  int /*<<< orphan*/  PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecInitResultSlot (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ExecInitResultTypeTL (int /*<<< orphan*/ *) ; 

void
ExecInitResultTupleSlotTL(PlanState *planstate,
						  const TupleTableSlotOps *tts_ops)
{
	ExecInitResultTypeTL(planstate);
	ExecInitResultSlot(planstate, tts_ops);
}