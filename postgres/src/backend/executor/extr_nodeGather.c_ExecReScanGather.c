#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ rescan_param; } ;
struct TYPE_10__ {scalar_t__ plan; } ;
struct TYPE_12__ {int initialized; TYPE_1__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/ * chgParam; } ;
typedef  TYPE_2__ PlanState ;
typedef  TYPE_3__ GatherState ;
typedef  TYPE_4__ Gather ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecShutdownGatherWorkers (TYPE_3__*) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* outerPlanState (TYPE_3__*) ; 

void
ExecReScanGather(GatherState *node)
{
	Gather	   *gather = (Gather *) node->ps.plan;
	PlanState  *outerPlan = outerPlanState(node);

	/* Make sure any existing workers are gracefully shut down */
	ExecShutdownGatherWorkers(node);

	/* Mark node so that shared state will be rebuilt at next call */
	node->initialized = false;

	/*
	 * Set child node's chgParam to tell it that the next scan might deliver a
	 * different set of rows within the leader process.  (The overall rowset
	 * shouldn't change, but the leader process's subset might; hence nodes
	 * between here and the parallel table scan node mustn't optimize on the
	 * assumption of an unchanging rowset.)
	 */
	if (gather->rescan_param >= 0)
		outerPlan->chgParam = bms_add_member(outerPlan->chgParam,
											 gather->rescan_param);

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