#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double startup_cost; double total_cost; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/  List ;
typedef  double Cost ;

/* Variables and functions */
 double APPEND_CPU_COST_MULTIPLIER ; 
 double LOG2 (double) ; 
 double cpu_operator_cost ; 
 double cpu_tuple_cost ; 

void
cost_merge_append(Path *path, PlannerInfo *root,
				  List *pathkeys, int n_streams,
				  Cost input_startup_cost, Cost input_total_cost,
				  double tuples)
{
	Cost		startup_cost = 0;
	Cost		run_cost = 0;
	Cost		comparison_cost;
	double		N;
	double		logN;

	/*
	 * Avoid log(0)...
	 */
	N = (n_streams < 2) ? 2.0 : (double) n_streams;
	logN = LOG2(N);

	/* Assumed cost per tuple comparison */
	comparison_cost = 2.0 * cpu_operator_cost;

	/* Heap creation cost */
	startup_cost += comparison_cost * N * logN;

	/* Per-tuple heap maintenance cost */
	run_cost += tuples * comparison_cost * logN;

	/*
	 * Although MergeAppend does not do any selection or projection, it's not
	 * free; add a small per-tuple overhead.
	 */
	run_cost += cpu_tuple_cost * APPEND_CPU_COST_MULTIPLIER * tuples;

	path->startup_cost = startup_cost + input_startup_cost;
	path->total_cost = startup_cost + run_cost + input_total_cost;
}