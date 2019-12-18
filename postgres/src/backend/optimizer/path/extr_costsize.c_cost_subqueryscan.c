#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int ppi_rows; } ;
struct TYPE_21__ {int startup; int per_tuple; } ;
struct TYPE_20__ {scalar_t__ relid; scalar_t__ rtekind; int rows; int tuples; } ;
struct TYPE_18__ {int rows; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; TYPE_3__* pathtarget; } ;
struct TYPE_19__ {TYPE_4__ path; TYPE_1__* subpath; } ;
struct TYPE_16__ {int startup; int per_tuple; } ;
struct TYPE_17__ {TYPE_2__ cost; } ;
struct TYPE_15__ {int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
typedef  TYPE_5__ SubqueryScanPath ;
typedef  TYPE_6__ RelOptInfo ;
typedef  TYPE_7__ QualCost ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_8__ ParamPathInfo ;
typedef  int Cost ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_SUBQUERY ; 
 int cpu_tuple_cost ; 
 int /*<<< orphan*/  get_restriction_qual_cost (int /*<<< orphan*/ *,TYPE_6__*,TYPE_8__*,TYPE_7__*) ; 

void
cost_subqueryscan(SubqueryScanPath *path, PlannerInfo *root,
				  RelOptInfo *baserel, ParamPathInfo *param_info)
{
	Cost		startup_cost;
	Cost		run_cost;
	QualCost	qpqual_cost;
	Cost		cpu_per_tuple;

	/* Should only be applied to base relations that are subqueries */
	Assert(baserel->relid > 0);
	Assert(baserel->rtekind == RTE_SUBQUERY);

	/* Mark the path with the correct row estimate */
	if (param_info)
		path->path.rows = param_info->ppi_rows;
	else
		path->path.rows = baserel->rows;

	/*
	 * Cost of path is cost of evaluating the subplan, plus cost of evaluating
	 * any restriction clauses and tlist that will be attached to the
	 * SubqueryScan node, plus cpu_tuple_cost to account for selection and
	 * projection overhead.
	 */
	path->path.startup_cost = path->subpath->startup_cost;
	path->path.total_cost = path->subpath->total_cost;

	get_restriction_qual_cost(root, baserel, param_info, &qpqual_cost);

	startup_cost = qpqual_cost.startup;
	cpu_per_tuple = cpu_tuple_cost + qpqual_cost.per_tuple;
	run_cost = cpu_per_tuple * baserel->tuples;

	/* tlist eval costs are paid per output row, not per tuple scanned */
	startup_cost += path->path.pathtarget->cost.startup;
	run_cost += path->path.pathtarget->cost.per_tuple * path->path.rows;

	path->path.startup_cost += startup_cost;
	path->path.total_cost += startup_cost + run_cost;
}