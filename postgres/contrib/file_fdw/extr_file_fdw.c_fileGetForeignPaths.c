#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lateral_relids; int /*<<< orphan*/  rows; scalar_t__ fdw_private; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  FileFdwPlanState ;
typedef  int /*<<< orphan*/  Cost ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  add_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ check_selective_binary_conversion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ create_foreignscan_path (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  estimate_costs (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeDefElem (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
fileGetForeignPaths(PlannerInfo *root,
					RelOptInfo *baserel,
					Oid foreigntableid)
{
	FileFdwPlanState *fdw_private = (FileFdwPlanState *) baserel->fdw_private;
	Cost		startup_cost;
	Cost		total_cost;
	List	   *columns;
	List	   *coptions = NIL;

	/* Decide whether to selectively perform binary conversion */
	if (check_selective_binary_conversion(baserel,
										  foreigntableid,
										  &columns))
		coptions = list_make1(makeDefElem("convert_selectively",
										  (Node *) columns, -1));

	/* Estimate costs */
	estimate_costs(root, baserel, fdw_private,
				   &startup_cost, &total_cost);

	/*
	 * Create a ForeignPath node and add it as only possible path.  We use the
	 * fdw_private list of the path to carry the convert_selectively option;
	 * it will be propagated into the fdw_private list of the Plan node.
	 *
	 * We don't support pushing join clauses into the quals of this path, but
	 * it could still have required parameterization due to LATERAL refs in
	 * its tlist.
	 */
	add_path(baserel, (Path *)
			 create_foreignscan_path(root, baserel,
									 NULL,	/* default pathtarget */
									 baserel->rows,
									 startup_cost,
									 total_cost,
									 NIL,	/* no pathkeys */
									 baserel->lateral_relids,
									 NULL,	/* no extra plan */
									 coptions));

	/*
	 * If data file was sorted, and we knew it somehow, we could insert
	 * appropriate pathkeys into the ForeignPath node to tell the planner
	 * that.
	 */
}