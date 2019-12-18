#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  plan; } ;
struct TYPE_14__ {int /*<<< orphan*/  path; int /*<<< orphan*/  single_copy; int /*<<< orphan*/  num_workers; int /*<<< orphan*/  subpath; } ;
struct TYPE_13__ {TYPE_1__* glob; } ;
struct TYPE_12__ {int parallelModeNeeded; } ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ GatherPath ;
typedef  TYPE_4__ Gather ;

/* Variables and functions */
 int /*<<< orphan*/  CP_EXACT_TLIST ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  assign_special_exec_param (TYPE_2__*) ; 
 int /*<<< orphan*/ * build_path_tlist (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_plan_recurse (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* make_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Gather *
create_gather_plan(PlannerInfo *root, GatherPath *best_path)
{
	Gather	   *gather_plan;
	Plan	   *subplan;
	List	   *tlist;

	/*
	 * Although the Gather node can project, we prefer to push down such work
	 * to its child node, so demand an exact tlist from the child.
	 */
	subplan = create_plan_recurse(root, best_path->subpath, CP_EXACT_TLIST);

	tlist = build_path_tlist(root, &best_path->path);

	gather_plan = make_gather(tlist,
							  NIL,
							  best_path->num_workers,
							  assign_special_exec_param(root),
							  best_path->single_copy,
							  subplan);

	copy_generic_path_info(&gather_plan->plan, &best_path->path);

	/* use parallel mode for parallel plans. */
	root->glob->parallelModeNeeded = true;

	return gather_plan;
}