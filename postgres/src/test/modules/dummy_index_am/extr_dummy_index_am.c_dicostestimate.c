#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  IndexPath ;
typedef  double Cost ;

/* Variables and functions */

__attribute__((used)) static void
dicostestimate(PlannerInfo *root, IndexPath *path, double loop_count,
			   Cost *indexStartupCost, Cost *indexTotalCost,
			   Selectivity *indexSelectivity, double *indexCorrelation,
			   double *indexPages)
{
	/* Tell planner to never use this index! */
	*indexStartupCost = 1.0e10;
	*indexTotalCost = 1.0e10;

	/* Do not care about the rest */
	*indexSelectivity = 1;
	*indexCorrelation = 0;
	*indexPages = 1;
}