#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_11__ {int as_nplans; int /*<<< orphan*/  as_whichplan; TYPE_1__ ps; TYPE_3__** appendplans; int /*<<< orphan*/ * as_valid_subplans; TYPE_2__* as_prune_state; } ;
struct TYPE_10__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_9__ {int /*<<< orphan*/  execparamids; } ;
typedef  TYPE_3__ PlanState ;
typedef  TYPE_4__ AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (TYPE_3__*) ; 
 int /*<<< orphan*/  INVALID_SUBPLAN_INDEX ; 
 int /*<<< orphan*/  UpdateChangedParamSet (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bms_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecReScanAppend(AppendState *node)
{
	int			i;

	/*
	 * If any PARAM_EXEC Params used in pruning expressions have changed, then
	 * we'd better unset the valid subplans so that they are reselected for
	 * the new parameter values.
	 */
	if (node->as_prune_state &&
		bms_overlap(node->ps.chgParam,
					node->as_prune_state->execparamids))
	{
		bms_free(node->as_valid_subplans);
		node->as_valid_subplans = NULL;
	}

	for (i = 0; i < node->as_nplans; i++)
	{
		PlanState  *subnode = node->appendplans[i];

		/*
		 * ExecReScan doesn't know about my subplans, so I have to do
		 * changed-parameter signaling myself.
		 */
		if (node->ps.chgParam != NULL)
			UpdateChangedParamSet(subnode, node->ps.chgParam);

		/*
		 * If chgParam of subnode is not null then plan will be re-scanned by
		 * first ExecProcNode.
		 */
		if (subnode->chgParam == NULL)
			ExecReScan(subnode);
	}

	/* Let choose_next_subplan_* function handle setting the first subplan */
	node->as_whichplan = INVALID_SUBPLAN_INDEX;
}