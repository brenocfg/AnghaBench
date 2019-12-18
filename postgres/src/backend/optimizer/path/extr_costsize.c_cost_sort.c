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
struct TYPE_3__ {double rows; double startup_cost; double total_cost; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/  List ;
typedef  double Cost ;

/* Variables and functions */
 double BLCKSZ ; 
 double LOG2 (double) ; 
 double ceil (double) ; 
 double cpu_operator_cost ; 
 double disable_cost ; 
 int /*<<< orphan*/  enable_sort ; 
 double log (double) ; 
 double random_page_cost ; 
 double relation_byte_size (double,int) ; 
 double seq_page_cost ; 
 double tuplesort_merge_order (long) ; 

void
cost_sort(Path *path, PlannerInfo *root,
		  List *pathkeys, Cost input_cost, double tuples, int width,
		  Cost comparison_cost, int sort_mem,
		  double limit_tuples)
{
	Cost		startup_cost = input_cost;
	Cost		run_cost = 0;
	double		input_bytes = relation_byte_size(tuples, width);
	double		output_bytes;
	double		output_tuples;
	long		sort_mem_bytes = sort_mem * 1024L;

	if (!enable_sort)
		startup_cost += disable_cost;

	path->rows = tuples;

	/*
	 * We want to be sure the cost of a sort is never estimated as zero, even
	 * if passed-in tuple count is zero.  Besides, mustn't do log(0)...
	 */
	if (tuples < 2.0)
		tuples = 2.0;

	/* Include the default cost-per-comparison */
	comparison_cost += 2.0 * cpu_operator_cost;

	/* Do we have a useful LIMIT? */
	if (limit_tuples > 0 && limit_tuples < tuples)
	{
		output_tuples = limit_tuples;
		output_bytes = relation_byte_size(output_tuples, width);
	}
	else
	{
		output_tuples = tuples;
		output_bytes = input_bytes;
	}

	if (output_bytes > sort_mem_bytes)
	{
		/*
		 * We'll have to use a disk-based sort of all the tuples
		 */
		double		npages = ceil(input_bytes / BLCKSZ);
		double		nruns = input_bytes / sort_mem_bytes;
		double		mergeorder = tuplesort_merge_order(sort_mem_bytes);
		double		log_runs;
		double		npageaccesses;

		/*
		 * CPU costs
		 *
		 * Assume about N log2 N comparisons
		 */
		startup_cost += comparison_cost * tuples * LOG2(tuples);

		/* Disk costs */

		/* Compute logM(r) as log(r) / log(M) */
		if (nruns > mergeorder)
			log_runs = ceil(log(nruns) / log(mergeorder));
		else
			log_runs = 1.0;
		npageaccesses = 2.0 * npages * log_runs;
		/* Assume 3/4ths of accesses are sequential, 1/4th are not */
		startup_cost += npageaccesses *
			(seq_page_cost * 0.75 + random_page_cost * 0.25);
	}
	else if (tuples > 2 * output_tuples || input_bytes > sort_mem_bytes)
	{
		/*
		 * We'll use a bounded heap-sort keeping just K tuples in memory, for
		 * a total number of tuple comparisons of N log2 K; but the constant
		 * factor is a bit higher than for quicksort.  Tweak it so that the
		 * cost curve is continuous at the crossover point.
		 */
		startup_cost += comparison_cost * tuples * LOG2(2.0 * output_tuples);
	}
	else
	{
		/* We'll use plain quicksort on all the input tuples */
		startup_cost += comparison_cost * tuples * LOG2(tuples);
	}

	/*
	 * Also charge a small amount (arbitrarily set equal to operator cost) per
	 * extracted tuple.  We don't charge cpu_tuple_cost because a Sort node
	 * doesn't do qual-checking or projection, so it has less overhead than
	 * most plan nodes.  Note it's correct to use tuples not output_tuples
	 * here --- the upper LIMIT will pro-rate the run cost so we'd be double
	 * counting the LIMIT otherwise.
	 */
	run_cost += cpu_operator_cost * tuples;

	path->startup_cost = startup_cost;
	path->total_cost = startup_cost + run_cost;
}