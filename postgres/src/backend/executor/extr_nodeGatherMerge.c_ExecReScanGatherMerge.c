#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ rescan_param; } ;
struct TYPE_11__ {scalar_t__ plan; } ;
struct TYPE_13__ {int initialized; int gm_initialized; TYPE_1__ ps; } ;
struct TYPE_12__ {int /*<<< orphan*/ * chgParam; } ;
typedef  TYPE_2__ PlanState ;
typedef  TYPE_3__ GatherMergeState ;
typedef  TYPE_4__ GatherMerge ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecShutdownGatherMergeWorkers (TYPE_3__*) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gather_merge_clear_tuples (TYPE_3__*) ; 
 TYPE_2__* outerPlanState (TYPE_3__*) ; 

void
ExecReScanGatherMerge(GatherMergeState *node)
{
	GatherMerge *gm = (GatherMerge *) node->ps.plan;
	PlanState  *outerPlan = outerPlanState(node);

	/* Make sure any existing workers are gracefully shut down */
	ExecShutdownGatherMergeWorkers(node);

	/* Free any unused tuples, so we don't leak memory across rescans */
	gather_merge_clear_tuples(node);

	/* Mark node so that shared state will be rebuilt at next call */
	node->initialized = false;
	node->gm_initialized = false;

	/*
	 * Set child node's chgParam to tell it that the next scan might deliver a
	 * different set of rows within the leader process.  (The overall rowset
	 * shouldn't change, but the leader process's subset might; hence nodes
	 * between here and the parallel table scan node mustn't optimize on the
	 * assumption of an unchanging rowset.)
	 */
	if (gm->rescan_param >= 0)
		outerPlan->chgParam = bms_add_member(outerPlan->chgParam,
											 gm->rescan_param);

	/*
	 * If chgParam of subnode is not null then plan will be re-scanned by
	 * first ExecProcNode.  Note: because this does nothing if we have a
	 * rescan_param, it's currently guaranteed that parallel-aware child nodes
	 * will not see a ReScan call until after they get a ReInitializeDSM call.
	 * That ordering might not be something to rely on, though.  A good rule
	 * of thumb is that ReInitializeDSM should reset only shared state, ReScan
	 * should reset only local state, and anything that depends on both of
	 * those steps being finished must wait until the first ExecProcNode call.
	 */
	if (outerPlan->chgParam == NULL)
		ExecReScan(outerPlan);
}