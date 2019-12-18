#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  plan; } ;
struct TYPE_15__ {TYPE_2__ scan; } ;
struct TYPE_14__ {scalar_t__ param_info; TYPE_1__* parent; } ;
struct TYPE_13__ {scalar_t__ rtekind; int /*<<< orphan*/  funcordinality; int /*<<< orphan*/ * functions; } ;
struct TYPE_11__ {scalar_t__ relid; } ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_4__ Path ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ Index ;
typedef  TYPE_5__ FunctionScan ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_FUNCTION ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * extract_actual_clauses (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* make_functionscan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * order_qual_clauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* planner_rt_fetch (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ replace_nestloop_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FunctionScan *
create_functionscan_plan(PlannerInfo *root, Path *best_path,
						 List *tlist, List *scan_clauses)
{
	FunctionScan *scan_plan;
	Index		scan_relid = best_path->parent->relid;
	RangeTblEntry *rte;
	List	   *functions;

	/* it should be a function base rel... */
	Assert(scan_relid > 0);
	rte = planner_rt_fetch(scan_relid, root);
	Assert(rte->rtekind == RTE_FUNCTION);
	functions = rte->functions;

	/* Sort clauses into best execution order */
	scan_clauses = order_qual_clauses(root, scan_clauses);

	/* Reduce RestrictInfo list to bare expressions; ignore pseudoconstants */
	scan_clauses = extract_actual_clauses(scan_clauses, false);

	/* Replace any outer-relation variables with nestloop params */
	if (best_path->param_info)
	{
		scan_clauses = (List *)
			replace_nestloop_params(root, (Node *) scan_clauses);
		/* The function expressions could contain nestloop params, too */
		functions = (List *) replace_nestloop_params(root, (Node *) functions);
	}

	scan_plan = make_functionscan(tlist, scan_clauses, scan_relid,
								  functions, rte->funcordinality);

	copy_generic_path_info(&scan_plan->scan.plan, best_path);

	return scan_plan;
}