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
struct TYPE_7__ {scalar_t__ rtekind; scalar_t__ self_reference; } ;
struct TYPE_6__ {scalar_t__ relid; int tuples; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_CTE ; 
 TYPE_2__* planner_rt_fetch (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_baserel_size_estimates (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
set_cte_size_estimates(PlannerInfo *root, RelOptInfo *rel, double cte_rows)
{
	RangeTblEntry *rte;

	/* Should only be applied to base relations that are CTE references */
	Assert(rel->relid > 0);
	rte = planner_rt_fetch(rel->relid, root);
	Assert(rte->rtekind == RTE_CTE);

	if (rte->self_reference)
	{
		/*
		 * In a self-reference, arbitrarily assume the average worktable size
		 * is about 10 times the nonrecursive term's size.
		 */
		rel->tuples = 10 * cte_rows;
	}
	else
	{
		/* Otherwise just believe the CTE's rowcount estimate */
		rel->tuples = cte_rows;
	}

	/* Now estimate number of output rows, etc */
	set_baserel_size_estimates(root, rel);
}