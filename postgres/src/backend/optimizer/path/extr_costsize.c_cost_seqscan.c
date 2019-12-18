#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {double ppi_rows; } ;
struct TYPE_18__ {double rows; scalar_t__ parallel_workers; double startup_cost; double total_cost; TYPE_2__* pathtarget; } ;
struct TYPE_17__ {double startup; double per_tuple; } ;
struct TYPE_16__ {scalar_t__ relid; scalar_t__ rtekind; double rows; double pages; double tuples; int /*<<< orphan*/  reltablespace; } ;
struct TYPE_14__ {double startup; double per_tuple; } ;
struct TYPE_15__ {TYPE_1__ cost; } ;
typedef  TYPE_3__ RelOptInfo ;
typedef  TYPE_4__ QualCost ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_5__ Path ;
typedef  TYPE_6__ ParamPathInfo ;
typedef  double Cost ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_RELATION ; 
 double clamp_row_est (double) ; 
 double cpu_tuple_cost ; 
 double disable_cost ; 
 int /*<<< orphan*/  enable_seqscan ; 
 double get_parallel_divisor (TYPE_5__*) ; 
 int /*<<< orphan*/  get_restriction_qual_cost (int /*<<< orphan*/ *,TYPE_3__*,TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  get_tablespace_page_costs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double*) ; 

void
cost_seqscan(Path *path, PlannerInfo *root,
			 RelOptInfo *baserel, ParamPathInfo *param_info)
{
	Cost		startup_cost = 0;
	Cost		cpu_run_cost;
	Cost		disk_run_cost;
	double		spc_seq_page_cost;
	QualCost	qpqual_cost;
	Cost		cpu_per_tuple;

	/* Should only be applied to base relations */
	Assert(baserel->relid > 0);
	Assert(baserel->rtekind == RTE_RELATION);

	/* Mark the path with the correct row estimate */
	if (param_info)
		path->rows = param_info->ppi_rows;
	else
		path->rows = baserel->rows;

	if (!enable_seqscan)
		startup_cost += disable_cost;

	/* fetch estimated page cost for tablespace containing table */
	get_tablespace_page_costs(baserel->reltablespace,
							  NULL,
							  &spc_seq_page_cost);

	/*
	 * disk costs
	 */
	disk_run_cost = spc_seq_page_cost * baserel->pages;

	/* CPU costs */
	get_restriction_qual_cost(root, baserel, param_info, &qpqual_cost);

	startup_cost += qpqual_cost.startup;
	cpu_per_tuple = cpu_tuple_cost + qpqual_cost.per_tuple;
	cpu_run_cost = cpu_per_tuple * baserel->tuples;
	/* tlist eval costs are paid per output row, not per tuple scanned */
	startup_cost += path->pathtarget->cost.startup;
	cpu_run_cost += path->pathtarget->cost.per_tuple * path->rows;

	/* Adjust costing for parallelism, if used. */
	if (path->parallel_workers > 0)
	{
		double		parallel_divisor = get_parallel_divisor(path);

		/* The CPU cost is divided among all the workers. */
		cpu_run_cost /= parallel_divisor;

		/*
		 * It may be possible to amortize some of the I/O cost, but probably
		 * not very much, because most operating systems already do aggressive
		 * prefetching.  For now, we assume that the disk run cost can't be
		 * amortized at all.
		 */

		/*
		 * In the case of a parallel plan, the row count needs to represent
		 * the number of tuples processed per worker.
		 */
		path->rows = clamp_row_est(path->rows / parallel_divisor);
	}

	path->startup_cost = startup_cost;
	path->total_cost = startup_cost + cpu_run_cost + disk_run_cost;
}