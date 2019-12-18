#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int startup_cost; int total_cost; double rows; TYPE_1__* pathtarget; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ Path ;
typedef  int Cost ;

/* Variables and functions */
 int /*<<< orphan*/  Max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double cpu_tuple_cost ; 

void
cost_recursive_union(Path *runion, Path *nrterm, Path *rterm)
{
	Cost		startup_cost;
	Cost		total_cost;
	double		total_rows;

	/* We probably have decent estimates for the non-recursive term */
	startup_cost = nrterm->startup_cost;
	total_cost = nrterm->total_cost;
	total_rows = nrterm->rows;

	/*
	 * We arbitrarily assume that about 10 recursive iterations will be
	 * needed, and that we've managed to get a good fix on the cost and output
	 * size of each one of them.  These are mighty shaky assumptions but it's
	 * hard to see how to do better.
	 */
	total_cost += 10 * rterm->total_cost;
	total_rows += 10 * rterm->rows;

	/*
	 * Also charge cpu_tuple_cost per row to account for the costs of
	 * manipulating the tuplestores.  (We don't worry about possible
	 * spill-to-disk costs.)
	 */
	total_cost += cpu_tuple_cost * total_rows;

	runion->startup_cost = startup_cost;
	runion->total_cost = total_cost;
	runion->rows = total_rows;
	runion->pathtarget->width = Max(nrterm->pathtarget->width,
									rterm->pathtarget->width);
}