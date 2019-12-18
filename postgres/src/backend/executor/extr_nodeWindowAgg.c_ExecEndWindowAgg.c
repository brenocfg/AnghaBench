#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ps_ExprContext; } ;
struct TYPE_8__ {TYPE_6__ ps; scalar_t__ ss_ScanTupleSlot; } ;
struct TYPE_9__ {int numaggs; scalar_t__ aggcontext; scalar_t__ partcontext; TYPE_4__* peragg; TYPE_4__* perfunc; TYPE_1__ ss; int /*<<< orphan*/  tmpcontext; scalar_t__ frametail_slot; scalar_t__ framehead_slot; scalar_t__ temp_slot_2; scalar_t__ temp_slot_1; scalar_t__ agg_row_slot; scalar_t__ first_part_slot; } ;
typedef  TYPE_2__ WindowAggState ;
struct TYPE_10__ {scalar_t__ aggcontext; } ;
typedef  int /*<<< orphan*/  PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_6__*) ; 
 int /*<<< orphan*/  MemoryContextDelete (scalar_t__) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (TYPE_4__*) ; 
 int /*<<< orphan*/  release_partition (TYPE_2__*) ; 

void
ExecEndWindowAgg(WindowAggState *node)
{
	PlanState  *outerPlan;
	int			i;

	release_partition(node);

	ExecClearTuple(node->ss.ss_ScanTupleSlot);
	ExecClearTuple(node->first_part_slot);
	ExecClearTuple(node->agg_row_slot);
	ExecClearTuple(node->temp_slot_1);
	ExecClearTuple(node->temp_slot_2);
	if (node->framehead_slot)
		ExecClearTuple(node->framehead_slot);
	if (node->frametail_slot)
		ExecClearTuple(node->frametail_slot);

	/*
	 * Free both the expr contexts.
	 */
	ExecFreeExprContext(&node->ss.ps);
	node->ss.ps.ps_ExprContext = node->tmpcontext;
	ExecFreeExprContext(&node->ss.ps);

	for (i = 0; i < node->numaggs; i++)
	{
		if (node->peragg[i].aggcontext != node->aggcontext)
			MemoryContextDelete(node->peragg[i].aggcontext);
	}
	MemoryContextDelete(node->partcontext);
	MemoryContextDelete(node->aggcontext);

	pfree(node->perfunc);
	pfree(node->peragg);

	outerPlan = outerPlanState(node);
	ExecEndNode(outerPlan);
}