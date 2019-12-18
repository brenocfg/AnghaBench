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
typedef  int /*<<< orphan*/  Tuplesortstate ;
struct TYPE_12__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_10__ {int /*<<< orphan*/  ps_ResultTupleSlot; } ;
struct TYPE_9__ {TYPE_2__ ps; } ;
struct TYPE_11__ {int sort_Done; scalar_t__ bounded; scalar_t__ bounded_Done; scalar_t__ bound; scalar_t__ bound_Done; int /*<<< orphan*/ * tuplesortstate; int /*<<< orphan*/  randomAccess; TYPE_1__ ss; } ;
typedef  TYPE_3__ SortState ;
typedef  TYPE_4__ PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecReScan (TYPE_4__*) ; 
 TYPE_4__* outerPlanState (TYPE_3__*) ; 
 int /*<<< orphan*/  tuplesort_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplesort_rescan (int /*<<< orphan*/ *) ; 

void
ExecReScanSort(SortState *node)
{
	PlanState  *outerPlan = outerPlanState(node);

	/*
	 * If we haven't sorted yet, just return. If outerplan's chgParam is not
	 * NULL then it will be re-scanned by ExecProcNode, else no reason to
	 * re-scan it at all.
	 */
	if (!node->sort_Done)
		return;

	/* must drop pointer to sort result tuple */
	ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);

	/*
	 * If subnode is to be rescanned then we forget previous sort results; we
	 * have to re-read the subplan and re-sort.  Also must re-sort if the
	 * bounded-sort parameters changed or we didn't select randomAccess.
	 *
	 * Otherwise we can just rewind and rescan the sorted output.
	 */
	if (outerPlan->chgParam != NULL ||
		node->bounded != node->bounded_Done ||
		node->bound != node->bound_Done ||
		!node->randomAccess)
	{
		node->sort_Done = false;
		tuplesort_end((Tuplesortstate *) node->tuplesortstate);
		node->tuplesortstate = NULL;

		/*
		 * if chgParam of subnode is not null then plan will be re-scanned by
		 * first ExecProcNode.
		 */
		if (outerPlan->chgParam == NULL)
			ExecReScan(outerPlan);
	}
	else
		tuplesort_rescan((Tuplesortstate *) node->tuplesortstate);
}