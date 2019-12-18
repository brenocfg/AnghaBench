#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  costs ;
struct TYPE_10__ {int indexStartupCost; int indexTotalCost; int num_sa_scans; double indexCorrelation; double numIndexPages; int /*<<< orphan*/  indexSelectivity; } ;
struct TYPE_9__ {int tree_height; int pages; int tuples; } ;
struct TYPE_8__ {TYPE_2__* indexinfo; } ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ IndexPath ;
typedef  TYPE_2__ IndexOptInfo ;
typedef  TYPE_3__ GenericCosts ;
typedef  int Cost ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int ceil (int) ; 
 int cpu_operator_cost ; 
 int /*<<< orphan*/  genericcostestimate (int /*<<< orphan*/ *,TYPE_1__*,double,TYPE_3__*) ; 
 int log (double) ; 

void
gistcostestimate(PlannerInfo *root, IndexPath *path, double loop_count,
				 Cost *indexStartupCost, Cost *indexTotalCost,
				 Selectivity *indexSelectivity, double *indexCorrelation,
				 double *indexPages)
{
	IndexOptInfo *index = path->indexinfo;
	GenericCosts costs;
	Cost		descentCost;

	MemSet(&costs, 0, sizeof(costs));

	genericcostestimate(root, path, loop_count, &costs);

	/*
	 * We model index descent costs similarly to those for btree, but to do
	 * that we first need an idea of the tree height.  We somewhat arbitrarily
	 * assume that the fanout is 100, meaning the tree height is at most
	 * log100(index->pages).
	 *
	 * Although this computation isn't really expensive enough to require
	 * caching, we might as well use index->tree_height to cache it.
	 */
	if (index->tree_height < 0) /* unknown? */
	{
		if (index->pages > 1)	/* avoid computing log(0) */
			index->tree_height = (int) (log(index->pages) / log(100.0));
		else
			index->tree_height = 0;
	}

	/*
	 * Add a CPU-cost component to represent the costs of initial descent. We
	 * just use log(N) here not log2(N) since the branching factor isn't
	 * necessarily two anyway.  As for btree, charge once per SA scan.
	 */
	if (index->tuples > 1)		/* avoid computing log(0) */
	{
		descentCost = ceil(log(index->tuples)) * cpu_operator_cost;
		costs.indexStartupCost += descentCost;
		costs.indexTotalCost += costs.num_sa_scans * descentCost;
	}

	/*
	 * Likewise add a per-page charge, calculated the same as for btrees.
	 */
	descentCost = (index->tree_height + 1) * 50.0 * cpu_operator_cost;
	costs.indexStartupCost += descentCost;
	costs.indexTotalCost += costs.num_sa_scans * descentCost;

	*indexStartupCost = costs.indexStartupCost;
	*indexTotalCost = costs.indexTotalCost;
	*indexSelectivity = costs.indexSelectivity;
	*indexCorrelation = costs.indexCorrelation;
	*indexPages = costs.numIndexPages;
}