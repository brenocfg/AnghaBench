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
struct TYPE_6__ {int /*<<< orphan*/  firstFlag; int /*<<< orphan*/  flagColIdx; int /*<<< orphan*/  distinctList; int /*<<< orphan*/  strategy; int /*<<< orphan*/  cmd; int /*<<< orphan*/  numGroups; int /*<<< orphan*/  subpath; } ;
typedef  TYPE_1__ SetOpPath ;
typedef  TYPE_2__ SetOp ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int CP_LABEL_TLIST ; 
 scalar_t__ LONG_MAX ; 
 scalar_t__ Min (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_plan_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* make_setop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static SetOp *
create_setop_plan(PlannerInfo *root, SetOpPath *best_path, int flags)
{
	SetOp	   *plan;
	Plan	   *subplan;
	long		numGroups;

	/*
	 * SetOp doesn't project, so tlist requirements pass through; moreover we
	 * need grouping columns to be labeled.
	 */
	subplan = create_plan_recurse(root, best_path->subpath,
								  flags | CP_LABEL_TLIST);

	/* Convert numGroups to long int --- but 'ware overflow! */
	numGroups = (long) Min(best_path->numGroups, (double) LONG_MAX);

	plan = make_setop(best_path->cmd,
					  best_path->strategy,
					  subplan,
					  best_path->distinctList,
					  best_path->flagColIdx,
					  best_path->firstFlag,
					  numGroups);

	copy_generic_path_info(&plan->plan, (Path *) best_path);

	return plan;
}