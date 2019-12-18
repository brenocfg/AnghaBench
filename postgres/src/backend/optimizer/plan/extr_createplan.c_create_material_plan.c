#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  plan; } ;
struct TYPE_6__ {int /*<<< orphan*/  subpath; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Path ;
typedef  TYPE_1__ MaterialPath ;
typedef  TYPE_2__ Material ;

/* Variables and functions */
 int CP_SMALL_TLIST ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_plan_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* make_material (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Material *
create_material_plan(PlannerInfo *root, MaterialPath *best_path, int flags)
{
	Material   *plan;
	Plan	   *subplan;

	/*
	 * We don't want any excess columns in the materialized tuples, so request
	 * a smaller tlist.  Otherwise, since Material doesn't project, tlist
	 * requirements pass through.
	 */
	subplan = create_plan_recurse(root, best_path->subpath,
								  flags | CP_SMALL_TLIST);

	plan = make_material(subplan);

	copy_generic_path_info(&plan->plan, (Path *) best_path);

	return plan;
}