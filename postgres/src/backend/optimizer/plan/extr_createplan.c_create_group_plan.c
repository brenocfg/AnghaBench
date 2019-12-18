#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  plan; } ;
struct TYPE_10__ {int /*<<< orphan*/  groupClause; int /*<<< orphan*/  qual; int /*<<< orphan*/  path; int /*<<< orphan*/  subpath; } ;
struct TYPE_9__ {int /*<<< orphan*/  targetlist; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Plan ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ GroupPath ;
typedef  TYPE_3__ Group ;

/* Variables and functions */
 int /*<<< orphan*/  CP_LABEL_TLIST ; 
 int /*<<< orphan*/ * build_path_tlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_plan_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_grouping_collations (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_grouping_cols (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_grouping_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_length (int /*<<< orphan*/ ) ; 
 TYPE_3__* make_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * order_qual_clauses (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Group *
create_group_plan(PlannerInfo *root, GroupPath *best_path)
{
	Group	   *plan;
	Plan	   *subplan;
	List	   *tlist;
	List	   *quals;

	/*
	 * Group can project, so no need to be terribly picky about child tlist,
	 * but we do need grouping columns to be available
	 */
	subplan = create_plan_recurse(root, best_path->subpath, CP_LABEL_TLIST);

	tlist = build_path_tlist(root, &best_path->path);

	quals = order_qual_clauses(root, best_path->qual);

	plan = make_group(tlist,
					  quals,
					  list_length(best_path->groupClause),
					  extract_grouping_cols(best_path->groupClause,
											subplan->targetlist),
					  extract_grouping_ops(best_path->groupClause),
					  extract_grouping_collations(best_path->groupClause,
												  subplan->targetlist),
					  subplan);

	copy_generic_path_info(&plan->plan, (Path *) best_path);

	return plan;
}