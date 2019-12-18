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
struct TYPE_11__ {int /*<<< orphan*/  grpColIdx; int /*<<< orphan*/  numCols; } ;
struct TYPE_8__ {scalar_t__ plan; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_10__ {TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ GroupState ;
typedef  TYPE_4__ Group ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/ * lcons (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_3__*) ; 
 int /*<<< orphan*/  show_sort_group_keys (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_group_keys(GroupState *gstate, List *ancestors,
				ExplainState *es)
{
	Group	   *plan = (Group *) gstate->ss.ps.plan;

	/* The key columns refer to the tlist of the child plan */
	ancestors = lcons(gstate, ancestors);
	show_sort_group_keys(outerPlanState(gstate), "Group Key",
						 plan->numCols, plan->grpColIdx,
						 NULL, NULL, NULL,
						 ancestors, es);
	ancestors = list_delete_first(ancestors);
}