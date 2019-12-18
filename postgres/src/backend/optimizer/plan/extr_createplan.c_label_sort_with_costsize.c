#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
struct TYPE_9__ {int /*<<< orphan*/  parallel_safe; int /*<<< orphan*/  plan_width; int /*<<< orphan*/  plan_rows; int /*<<< orphan*/  total_cost; } ;
struct TYPE_7__ {int parallel_aware; int /*<<< orphan*/  parallel_safe; int /*<<< orphan*/  plan_width; int /*<<< orphan*/  plan_rows; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; TYPE_3__* lefttree; } ;
struct TYPE_8__ {TYPE_1__ plan; } ;
typedef  TYPE_2__ Sort ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ Plan ;
typedef  TYPE_4__ Path ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  cost_sort (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
label_sort_with_costsize(PlannerInfo *root, Sort *plan, double limit_tuples)
{
	Plan	   *lefttree = plan->plan.lefttree;
	Path		sort_path;		/* dummy for result of cost_sort */

	cost_sort(&sort_path, root, NIL,
			  lefttree->total_cost,
			  lefttree->plan_rows,
			  lefttree->plan_width,
			  0.0,
			  work_mem,
			  limit_tuples);
	plan->plan.startup_cost = sort_path.startup_cost;
	plan->plan.total_cost = sort_path.total_cost;
	plan->plan.plan_rows = lefttree->plan_rows;
	plan->plan.plan_width = lefttree->plan_width;
	plan->plan.parallel_aware = false;
	plan->plan.parallel_safe = lefttree->parallel_safe;
}