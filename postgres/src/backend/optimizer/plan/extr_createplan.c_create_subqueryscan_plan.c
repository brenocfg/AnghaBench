#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ param_info; TYPE_4__* parent; } ;
struct TYPE_12__ {scalar_t__ relid; scalar_t__ rtekind; int /*<<< orphan*/  subplan_params; int /*<<< orphan*/  subroot; } ;
struct TYPE_9__ {int /*<<< orphan*/  plan; } ;
struct TYPE_11__ {TYPE_1__ scan; } ;
struct TYPE_10__ {TYPE_8__ path; int /*<<< orphan*/  subpath; } ;
typedef  TYPE_2__ SubqueryScanPath ;
typedef  TYPE_3__ SubqueryScan ;
typedef  TYPE_4__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_SUBQUERY ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/ * create_plan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extract_actual_clauses (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* make_subqueryscan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * order_qual_clauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_subquery_nestloop_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ replace_nestloop_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SubqueryScan *
create_subqueryscan_plan(PlannerInfo *root, SubqueryScanPath *best_path,
						 List *tlist, List *scan_clauses)
{
	SubqueryScan *scan_plan;
	RelOptInfo *rel = best_path->path.parent;
	Index		scan_relid = rel->relid;
	Plan	   *subplan;

	/* it should be a subquery base rel... */
	Assert(scan_relid > 0);
	Assert(rel->rtekind == RTE_SUBQUERY);

	/*
	 * Recursively create Plan from Path for subquery.  Since we are entering
	 * a different planner context (subroot), recurse to create_plan not
	 * create_plan_recurse.
	 */
	subplan = create_plan(rel->subroot, best_path->subpath);

	/* Sort clauses into best execution order */
	scan_clauses = order_qual_clauses(root, scan_clauses);

	/* Reduce RestrictInfo list to bare expressions; ignore pseudoconstants */
	scan_clauses = extract_actual_clauses(scan_clauses, false);

	/* Replace any outer-relation variables with nestloop params */
	if (best_path->path.param_info)
	{
		scan_clauses = (List *)
			replace_nestloop_params(root, (Node *) scan_clauses);
		process_subquery_nestloop_params(root,
										 rel->subplan_params);
	}

	scan_plan = make_subqueryscan(tlist,
								  scan_clauses,
								  scan_relid,
								  subplan);

	copy_generic_path_info(&scan_plan->scan.plan, &best_path->path);

	return scan_plan;
}