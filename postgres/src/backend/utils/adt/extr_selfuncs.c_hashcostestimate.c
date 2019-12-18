#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  costs ;
struct TYPE_4__ {double indexCorrelation; double numIndexPages; int /*<<< orphan*/  indexSelectivity; int /*<<< orphan*/  indexTotalCost; int /*<<< orphan*/  indexStartupCost; } ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  IndexPath ;
typedef  TYPE_1__ GenericCosts ;
typedef  int /*<<< orphan*/  Cost ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genericcostestimate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,TYPE_1__*) ; 

void
hashcostestimate(PlannerInfo *root, IndexPath *path, double loop_count,
				 Cost *indexStartupCost, Cost *indexTotalCost,
				 Selectivity *indexSelectivity, double *indexCorrelation,
				 double *indexPages)
{
	GenericCosts costs;

	MemSet(&costs, 0, sizeof(costs));

	genericcostestimate(root, path, loop_count, &costs);

	/*
	 * A hash index has no descent costs as such, since the index AM can go
	 * directly to the target bucket after computing the hash value.  There
	 * are a couple of other hash-specific costs that we could conceivably add
	 * here, though:
	 *
	 * Ideally we'd charge spc_random_page_cost for each page in the target
	 * bucket, not just the numIndexPages pages that genericcostestimate
	 * thought we'd visit.  However in most cases we don't know which bucket
	 * that will be.  There's no point in considering the average bucket size
	 * because the hash AM makes sure that's always one page.
	 *
	 * Likewise, we could consider charging some CPU for each index tuple in
	 * the bucket, if we knew how many there were.  But the per-tuple cost is
	 * just a hash value comparison, not a general datatype-dependent
	 * comparison, so any such charge ought to be quite a bit less than
	 * cpu_operator_cost; which makes it probably not worth worrying about.
	 *
	 * A bigger issue is that chance hash-value collisions will result in
	 * wasted probes into the heap.  We don't currently attempt to model this
	 * cost on the grounds that it's rare, but maybe it's not rare enough.
	 * (Any fix for this ought to consider the generic lossy-operator problem,
	 * though; it's not entirely hash-specific.)
	 */

	*indexStartupCost = costs.indexStartupCost;
	*indexTotalCost = costs.indexTotalCost;
	*indexSelectivity = costs.indexSelectivity;
	*indexCorrelation = costs.indexCorrelation;
	*indexPages = costs.numIndexPages;
}