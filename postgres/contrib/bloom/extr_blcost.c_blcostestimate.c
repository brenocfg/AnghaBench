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
struct TYPE_10__ {double indexCorrelation; double numIndexPages; int /*<<< orphan*/  indexSelectivity; int /*<<< orphan*/  indexTotalCost; int /*<<< orphan*/  indexStartupCost; int /*<<< orphan*/  numIndexTuples; } ;
struct TYPE_9__ {int /*<<< orphan*/  tuples; } ;
struct TYPE_8__ {TYPE_2__* indexinfo; } ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ IndexPath ;
typedef  TYPE_2__ IndexOptInfo ;
typedef  TYPE_3__ GenericCosts ;
typedef  int /*<<< orphan*/  Cost ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genericcostestimate (int /*<<< orphan*/ *,TYPE_1__*,double,TYPE_3__*) ; 

void
blcostestimate(PlannerInfo *root, IndexPath *path, double loop_count,
			   Cost *indexStartupCost, Cost *indexTotalCost,
			   Selectivity *indexSelectivity, double *indexCorrelation,
			   double *indexPages)
{
	IndexOptInfo *index = path->indexinfo;
	GenericCosts costs;

	MemSet(&costs, 0, sizeof(costs));

	/* We have to visit all index tuples anyway */
	costs.numIndexTuples = index->tuples;

	/* Use generic estimate */
	genericcostestimate(root, path, loop_count, &costs);

	*indexStartupCost = costs.indexStartupCost;
	*indexTotalCost = costs.indexTotalCost;
	*indexSelectivity = costs.indexSelectivity;
	*indexCorrelation = costs.indexCorrelation;
	*indexPages = costs.numIndexPages;
}