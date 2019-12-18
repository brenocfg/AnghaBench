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
struct TYPE_12__ {scalar_t__ numCols; int /*<<< orphan*/  grpColIdx; scalar_t__ groupingSets; } ;
struct TYPE_9__ {scalar_t__ plan; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_11__ {TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExplainState ;
typedef  TYPE_3__ AggState ;
typedef  TYPE_4__ Agg ;

/* Variables and functions */
 int /*<<< orphan*/ * lcons (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_3__*) ; 
 int /*<<< orphan*/  show_grouping_sets (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_sort_group_keys (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_agg_keys(AggState *astate, List *ancestors,
			  ExplainState *es)
{
	Agg		   *plan = (Agg *) astate->ss.ps.plan;

	if (plan->numCols > 0 || plan->groupingSets)
	{
		/* The key columns refer to the tlist of the child plan */
		ancestors = lcons(astate, ancestors);

		if (plan->groupingSets)
			show_grouping_sets(outerPlanState(astate), plan, ancestors, es);
		else
			show_sort_group_keys(outerPlanState(astate), "Group Key",
								 plan->numCols, plan->grpColIdx,
								 NULL, NULL, NULL,
								 ancestors, es);

		ancestors = list_delete_first(ancestors);
	}
}