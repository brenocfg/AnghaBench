#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
struct TYPE_7__ {int parallel_aware; int /*<<< orphan*/  parallel_safe; int /*<<< orphan*/  plan_width; int /*<<< orphan*/  plan_rows; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; int /*<<< orphan*/  initPlan; } ;
typedef  TYPE_1__ Plan ;
typedef  TYPE_2__ Path ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  cost_material (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ make_material (TYPE_1__*) ; 

Plan *
materialize_finished_plan(Plan *subplan)
{
	Plan	   *matplan;
	Path		matpath;		/* dummy for result of cost_material */

	matplan = (Plan *) make_material(subplan);

	/*
	 * XXX horrid kluge: if there are any initPlans attached to the subplan,
	 * move them up to the Material node, which is now effectively the top
	 * plan node in its query level.  This prevents failure in
	 * SS_finalize_plan(), which see for comments.  We don't bother adjusting
	 * the subplan's cost estimate for this.
	 */
	matplan->initPlan = subplan->initPlan;
	subplan->initPlan = NIL;

	/* Set cost data */
	cost_material(&matpath,
				  subplan->startup_cost,
				  subplan->total_cost,
				  subplan->plan_rows,
				  subplan->plan_width);
	matplan->startup_cost = matpath.startup_cost;
	matplan->total_cost = matpath.total_cost;
	matplan->plan_rows = subplan->plan_rows;
	matplan->plan_width = subplan->plan_width;
	matplan->parallel_aware = false;
	matplan->parallel_safe = subplan->parallel_safe;

	return matplan;
}