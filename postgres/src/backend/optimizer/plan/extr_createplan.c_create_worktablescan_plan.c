#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  plan; } ;
struct TYPE_18__ {TYPE_2__ scan; } ;
typedef  TYPE_3__ WorkTableScan ;
struct TYPE_21__ {scalar_t__ param_info; TYPE_1__* parent; } ;
struct TYPE_20__ {scalar_t__ wt_param_id; struct TYPE_20__* parent_root; } ;
struct TYPE_19__ {scalar_t__ rtekind; int self_reference; scalar_t__ ctelevelsup; int /*<<< orphan*/  ctename; } ;
struct TYPE_16__ {scalar_t__ relid; } ;
typedef  TYPE_4__ RangeTblEntry ;
typedef  TYPE_5__ PlannerInfo ;
typedef  TYPE_6__ Path ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RTE_CTE ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extract_actual_clauses (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* make_worktablescan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * order_qual_clauses (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* planner_rt_fetch (scalar_t__,TYPE_5__*) ; 
 scalar_t__ replace_nestloop_params (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static WorkTableScan *
create_worktablescan_plan(PlannerInfo *root, Path *best_path,
						  List *tlist, List *scan_clauses)
{
	WorkTableScan *scan_plan;
	Index		scan_relid = best_path->parent->relid;
	RangeTblEntry *rte;
	Index		levelsup;
	PlannerInfo *cteroot;

	Assert(scan_relid > 0);
	rte = planner_rt_fetch(scan_relid, root);
	Assert(rte->rtekind == RTE_CTE);
	Assert(rte->self_reference);

	/*
	 * We need to find the worktable param ID, which is in the plan level
	 * that's processing the recursive UNION, which is one level *below* where
	 * the CTE comes from.
	 */
	levelsup = rte->ctelevelsup;
	if (levelsup == 0)			/* shouldn't happen */
		elog(ERROR, "bad levelsup for CTE \"%s\"", rte->ctename);
	levelsup--;
	cteroot = root;
	while (levelsup-- > 0)
	{
		cteroot = cteroot->parent_root;
		if (!cteroot)			/* shouldn't happen */
			elog(ERROR, "bad levelsup for CTE \"%s\"", rte->ctename);
	}
	if (cteroot->wt_param_id < 0)	/* shouldn't happen */
		elog(ERROR, "could not find param ID for CTE \"%s\"", rte->ctename);

	/* Sort clauses into best execution order */
	scan_clauses = order_qual_clauses(root, scan_clauses);

	/* Reduce RestrictInfo list to bare expressions; ignore pseudoconstants */
	scan_clauses = extract_actual_clauses(scan_clauses, false);

	/* Replace any outer-relation variables with nestloop params */
	if (best_path->param_info)
	{
		scan_clauses = (List *)
			replace_nestloop_params(root, (Node *) scan_clauses);
	}

	scan_plan = make_worktablescan(tlist, scan_clauses, scan_relid,
								   cteroot->wt_param_id);

	copy_generic_path_info(&scan_plan->scan.plan, best_path);

	return scan_plan;
}