#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nullsFirst; int /*<<< orphan*/  collations; int /*<<< orphan*/  sortOperators; int /*<<< orphan*/  sortColIdx; int /*<<< orphan*/  numCols; } ;
struct TYPE_5__ {scalar_t__ plan; } ;
struct TYPE_6__ {TYPE_1__ ps; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_2__ MergeAppendState ;
typedef  TYPE_3__ MergeAppend ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  show_sort_group_keys (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_merge_append_keys(MergeAppendState *mstate, List *ancestors,
					   ExplainState *es)
{
	MergeAppend *plan = (MergeAppend *) mstate->ps.plan;

	show_sort_group_keys((PlanState *) mstate, "Sort Key",
						 plan->numCols, plan->sortColIdx,
						 plan->sortOperators, plan->collations,
						 plan->nullsFirst,
						 ancestors, es);
}