#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_batches; } ;
struct TYPE_6__ {int pathtype; double total_cost; double startup_cost; double rows; TYPE_1__* pathtarget; } ;
struct TYPE_5__ {int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ Path ;
typedef  TYPE_3__ HashPath ;
typedef  double Cost ;

/* Variables and functions */
 double BLCKSZ ; 
#define  T_CteScan 133 
#define  T_FunctionScan 132 
#define  T_HashJoin 131 
#define  T_Material 130 
#define  T_Sort 129 
#define  T_WorkTableScan 128 
 double ceil (double) ; 
 double cpu_operator_cost ; 
 double cpu_tuple_cost ; 
 double relation_byte_size (double,int /*<<< orphan*/ ) ; 
 double seq_page_cost ; 
 long work_mem ; 

__attribute__((used)) static void
cost_rescan(PlannerInfo *root, Path *path,
			Cost *rescan_startup_cost,	/* output parameters */
			Cost *rescan_total_cost)
{
	switch (path->pathtype)
	{
		case T_FunctionScan:

			/*
			 * Currently, nodeFunctionscan.c always executes the function to
			 * completion before returning any rows, and caches the results in
			 * a tuplestore.  So the function eval cost is all startup cost
			 * and isn't paid over again on rescans. However, all run costs
			 * will be paid over again.
			 */
			*rescan_startup_cost = 0;
			*rescan_total_cost = path->total_cost - path->startup_cost;
			break;
		case T_HashJoin:

			/*
			 * If it's a single-batch join, we don't need to rebuild the hash
			 * table during a rescan.
			 */
			if (((HashPath *) path)->num_batches == 1)
			{
				/* Startup cost is exactly the cost of hash table building */
				*rescan_startup_cost = 0;
				*rescan_total_cost = path->total_cost - path->startup_cost;
			}
			else
			{
				/* Otherwise, no special treatment */
				*rescan_startup_cost = path->startup_cost;
				*rescan_total_cost = path->total_cost;
			}
			break;
		case T_CteScan:
		case T_WorkTableScan:
			{
				/*
				 * These plan types materialize their final result in a
				 * tuplestore or tuplesort object.  So the rescan cost is only
				 * cpu_tuple_cost per tuple, unless the result is large enough
				 * to spill to disk.
				 */
				Cost		run_cost = cpu_tuple_cost * path->rows;
				double		nbytes = relation_byte_size(path->rows,
														path->pathtarget->width);
				long		work_mem_bytes = work_mem * 1024L;

				if (nbytes > work_mem_bytes)
				{
					/* It will spill, so account for re-read cost */
					double		npages = ceil(nbytes / BLCKSZ);

					run_cost += seq_page_cost * npages;
				}
				*rescan_startup_cost = 0;
				*rescan_total_cost = run_cost;
			}
			break;
		case T_Material:
		case T_Sort:
			{
				/*
				 * These plan types not only materialize their results, but do
				 * not implement qual filtering or projection.  So they are
				 * even cheaper to rescan than the ones above.  We charge only
				 * cpu_operator_cost per tuple.  (Note: keep that in sync with
				 * the run_cost charge in cost_sort, and also see comments in
				 * cost_material before you change it.)
				 */
				Cost		run_cost = cpu_operator_cost * path->rows;
				double		nbytes = relation_byte_size(path->rows,
														path->pathtarget->width);
				long		work_mem_bytes = work_mem * 1024L;

				if (nbytes > work_mem_bytes)
				{
					/* It will spill, so account for re-read cost */
					double		npages = ceil(nbytes / BLCKSZ);

					run_cost += seq_page_cost * npages;
				}
				*rescan_startup_cost = 0;
				*rescan_total_cost = run_cost;
			}
			break;
		default:
			*rescan_startup_cost = path->startup_cost;
			*rescan_total_cost = path->total_cost;
			break;
	}
}