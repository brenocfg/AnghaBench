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
struct TYPE_9__ {double startup_cost; double total_cost; } ;
struct TYPE_8__ {int /*<<< orphan*/  group_pathkeys; TYPE_1__* parse; } ;
struct TYPE_7__ {int /*<<< orphan*/  groupClause; } ;
typedef  TYPE_2__ PlannerInfo ;
typedef  TYPE_3__ Path ;
typedef  int /*<<< orphan*/  List ;
typedef  double Cost ;

/* Variables and functions */
 double DEFAULT_FDW_SORT_MULTIPLIER ; 
 int /*<<< orphan*/  cost_sort (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,double,double,double,double,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  grouping_is_sortable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathkeys_contained_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
adjust_foreign_grouping_path_cost(PlannerInfo *root,
								  List *pathkeys,
								  double retrieved_rows,
								  double width,
								  double limit_tuples,
								  Cost *p_startup_cost,
								  Cost *p_run_cost)
{
	/*
	 * If the GROUP BY clause isn't sort-able, the plan chosen by the remote
	 * side is unlikely to generate properly-sorted output, so it would need
	 * an explicit sort; adjust the given costs with cost_sort().  Likewise,
	 * if the GROUP BY clause is sort-able but isn't a superset of the given
	 * pathkeys, adjust the costs with that function.  Otherwise, adjust the
	 * costs by applying the same heuristic as for the scan or join case.
	 */
	if (!grouping_is_sortable(root->parse->groupClause) ||
		!pathkeys_contained_in(pathkeys, root->group_pathkeys))
	{
		Path		sort_path;	/* dummy for result of cost_sort */

		cost_sort(&sort_path,
				  root,
				  pathkeys,
				  *p_startup_cost + *p_run_cost,
				  retrieved_rows,
				  width,
				  0.0,
				  work_mem,
				  limit_tuples);

		*p_startup_cost = sort_path.startup_cost;
		*p_run_cost = sort_path.total_cost - sort_path.startup_cost;
	}
	else
	{
		/*
		 * The default extra cost seems too large for foreign-grouping cases;
		 * add 1/4th of that default.
		 */
		double		sort_multiplier = 1.0 + (DEFAULT_FDW_SORT_MULTIPLIER
											 - 1.0) * 0.25;

		*p_startup_cost *= sort_multiplier;
		*p_run_cost *= sort_multiplier;
	}
}