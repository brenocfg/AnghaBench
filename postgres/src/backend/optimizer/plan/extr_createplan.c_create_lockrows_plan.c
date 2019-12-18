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
struct TYPE_6__ {int /*<<< orphan*/  epqParam; int /*<<< orphan*/  rowMarks; int /*<<< orphan*/  subpath; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Path ;
typedef  TYPE_1__ LockRowsPath ;
typedef  TYPE_2__ LockRows ;

/* Variables and functions */
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_plan_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* make_lockrows (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LockRows *
create_lockrows_plan(PlannerInfo *root, LockRowsPath *best_path,
					 int flags)
{
	LockRows   *plan;
	Plan	   *subplan;

	/* LockRows doesn't project, so tlist requirements pass through */
	subplan = create_plan_recurse(root, best_path->subpath, flags);

	plan = make_lockrows(subplan, best_path->rowMarks, best_path->epqParam);

	copy_generic_path_info(&plan->plan, (Path *) best_path);

	return plan;
}