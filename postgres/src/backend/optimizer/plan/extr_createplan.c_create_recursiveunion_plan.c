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
struct TYPE_6__ {int /*<<< orphan*/  distinctList; int /*<<< orphan*/  wtParam; int /*<<< orphan*/  numGroups; int /*<<< orphan*/  path; int /*<<< orphan*/  rightpath; int /*<<< orphan*/  leftpath; } ;
typedef  TYPE_1__ RecursiveUnionPath ;
typedef  TYPE_2__ RecursiveUnion ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CP_EXACT_TLIST ; 
 scalar_t__ LONG_MAX ; 
 scalar_t__ Min (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * build_path_tlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_plan_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* make_recursive_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static RecursiveUnion *
create_recursiveunion_plan(PlannerInfo *root, RecursiveUnionPath *best_path)
{
	RecursiveUnion *plan;
	Plan	   *leftplan;
	Plan	   *rightplan;
	List	   *tlist;
	long		numGroups;

	/* Need both children to produce same tlist, so force it */
	leftplan = create_plan_recurse(root, best_path->leftpath, CP_EXACT_TLIST);
	rightplan = create_plan_recurse(root, best_path->rightpath, CP_EXACT_TLIST);

	tlist = build_path_tlist(root, &best_path->path);

	/* Convert numGroups to long int --- but 'ware overflow! */
	numGroups = (long) Min(best_path->numGroups, (double) LONG_MAX);

	plan = make_recursive_union(tlist,
								leftplan,
								rightplan,
								best_path->wtParam,
								best_path->distinctList,
								numGroups);

	copy_generic_path_info(&plan->plan, (Path *) best_path);

	return plan;
}