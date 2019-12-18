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
struct TYPE_11__ {double inner_run_cost; double inner_rescan_run_cost; double startup_cost; double total_cost; double run_cost; } ;
struct TYPE_10__ {scalar_t__ inner_unique; } ;
struct TYPE_9__ {double rows; double startup_cost; double total_cost; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Path ;
typedef  scalar_t__ JoinType ;
typedef  TYPE_2__ JoinPathExtraData ;
typedef  TYPE_3__ JoinCostWorkspace ;
typedef  double Cost ;

/* Variables and functions */
 scalar_t__ JOIN_ANTI ; 
 scalar_t__ JOIN_SEMI ; 
 int /*<<< orphan*/  cost_rescan (int /*<<< orphan*/ *,TYPE_1__*,double*,double*) ; 

void
initial_cost_nestloop(PlannerInfo *root, JoinCostWorkspace *workspace,
					  JoinType jointype,
					  Path *outer_path, Path *inner_path,
					  JoinPathExtraData *extra)
{
	Cost		startup_cost = 0;
	Cost		run_cost = 0;
	double		outer_path_rows = outer_path->rows;
	Cost		inner_rescan_start_cost;
	Cost		inner_rescan_total_cost;
	Cost		inner_run_cost;
	Cost		inner_rescan_run_cost;

	/* estimate costs to rescan the inner relation */
	cost_rescan(root, inner_path,
				&inner_rescan_start_cost,
				&inner_rescan_total_cost);

	/* cost of source data */

	/*
	 * NOTE: clearly, we must pay both outer and inner paths' startup_cost
	 * before we can start returning tuples, so the join's startup cost is
	 * their sum.  We'll also pay the inner path's rescan startup cost
	 * multiple times.
	 */
	startup_cost += outer_path->startup_cost + inner_path->startup_cost;
	run_cost += outer_path->total_cost - outer_path->startup_cost;
	if (outer_path_rows > 1)
		run_cost += (outer_path_rows - 1) * inner_rescan_start_cost;

	inner_run_cost = inner_path->total_cost - inner_path->startup_cost;
	inner_rescan_run_cost = inner_rescan_total_cost - inner_rescan_start_cost;

	if (jointype == JOIN_SEMI || jointype == JOIN_ANTI ||
		extra->inner_unique)
	{
		/*
		 * With a SEMI or ANTI join, or if the innerrel is known unique, the
		 * executor will stop after the first match.
		 *
		 * Getting decent estimates requires inspection of the join quals,
		 * which we choose to postpone to final_cost_nestloop.
		 */

		/* Save private data for final_cost_nestloop */
		workspace->inner_run_cost = inner_run_cost;
		workspace->inner_rescan_run_cost = inner_rescan_run_cost;
	}
	else
	{
		/* Normal case; we'll scan whole input rel for each outer row */
		run_cost += inner_run_cost;
		if (outer_path_rows > 1)
			run_cost += (outer_path_rows - 1) * inner_rescan_run_cost;
	}

	/* CPU costs left for later */

	/* Public result fields */
	workspace->startup_cost = startup_cost;
	workspace->total_cost = startup_cost + run_cost;
	/* Save private data for final_cost_nestloop */
	workspace->run_cost = run_cost;
}