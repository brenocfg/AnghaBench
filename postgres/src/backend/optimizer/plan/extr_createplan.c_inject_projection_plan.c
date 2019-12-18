#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int parallel_safe; } ;
typedef  TYPE_1__ Plan ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  copy_plan_costsize (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ make_result (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Plan *
inject_projection_plan(Plan *subplan, List *tlist, bool parallel_safe)
{
	Plan	   *plan;

	plan = (Plan *) make_result(tlist, NULL, subplan);

	/*
	 * In principle, we should charge tlist eval cost plus cpu_per_tuple per
	 * row for the Result node.  But the former has probably been factored in
	 * already and the latter was not accounted for during Path construction,
	 * so being formally correct might just make the EXPLAIN output look less
	 * consistent not more so.  Hence, just copy the subplan's cost.
	 */
	copy_plan_costsize(plan, subplan);
	plan->parallel_safe = parallel_safe;

	return plan;
}