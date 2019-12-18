#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pathkeys; } ;
struct TYPE_8__ {int /*<<< orphan*/  numkeys; TYPE_1__ path; int /*<<< orphan*/  subpath; } ;
typedef  TYPE_2__ UpperUniquePath ;
struct TYPE_9__ {int /*<<< orphan*/  plan; } ;
typedef  TYPE_3__ Unique ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int CP_LABEL_TLIST ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_plan_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* make_unique_from_pathkeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Unique *
create_upper_unique_plan(PlannerInfo *root, UpperUniquePath *best_path, int flags)
{
	Unique	   *plan;
	Plan	   *subplan;

	/*
	 * Unique doesn't project, so tlist requirements pass through; moreover we
	 * need grouping columns to be labeled.
	 */
	subplan = create_plan_recurse(root, best_path->subpath,
								  flags | CP_LABEL_TLIST);

	plan = make_unique_from_pathkeys(subplan,
									 best_path->path.pathkeys,
									 best_path->numkeys);

	copy_generic_path_info(&plan->plan, (Path *) best_path);

	return plan;
}