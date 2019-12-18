#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ps_ResultTupleSlot; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_12__ {int eflags; int eof_underlying; int /*<<< orphan*/ * tuplestorestate; TYPE_2__ ss; } ;
struct TYPE_11__ {int /*<<< orphan*/ * chgParam; } ;
typedef  TYPE_3__ PlanState ;
typedef  TYPE_4__ MaterialState ;

/* Variables and functions */
 int EXEC_FLAG_REWIND ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecReScan (TYPE_3__*) ; 
 TYPE_3__* outerPlanState (TYPE_4__*) ; 
 int /*<<< orphan*/  tuplestore_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_rescan (int /*<<< orphan*/ *) ; 

void
ExecReScanMaterial(MaterialState *node)
{
	PlanState  *outerPlan = outerPlanState(node);

	ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);

	if (node->eflags != 0)
	{
		/*
		 * If we haven't materialized yet, just return. If outerplan's
		 * chgParam is not NULL then it will be re-scanned by ExecProcNode,
		 * else no reason to re-scan it at all.
		 */
		if (!node->tuplestorestate)
			return;

		/*
		 * If subnode is to be rescanned then we forget previous stored
		 * results; we have to re-read the subplan and re-store.  Also, if we
		 * told tuplestore it needn't support rescan, we lose and must
		 * re-read.  (This last should not happen in common cases; else our
		 * caller lied by not passing EXEC_FLAG_REWIND to us.)
		 *
		 * Otherwise we can just rewind and rescan the stored output. The
		 * state of the subnode does not change.
		 */
		if (outerPlan->chgParam != NULL ||
			(node->eflags & EXEC_FLAG_REWIND) == 0)
		{
			tuplestore_end(node->tuplestorestate);
			node->tuplestorestate = NULL;
			if (outerPlan->chgParam == NULL)
				ExecReScan(outerPlan);
			node->eof_underlying = false;
		}
		else
			tuplestore_rescan(node->tuplestorestate);
	}
	else
	{
		/* In this case we are just passing on the subquery's output */

		/*
		 * if chgParam of subnode is not null then plan will be re-scanned by
		 * first ExecProcNode.
		 */
		if (outerPlan->chgParam == NULL)
			ExecReScan(outerPlan);
		node->eof_underlying = false;
	}
}