#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rtekind; } ;
struct TYPE_5__ {scalar_t__ relid; int tuples; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_RESULT ; 
 TYPE_4__* planner_rt_fetch (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_baserel_size_estimates (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
set_result_size_estimates(PlannerInfo *root, RelOptInfo *rel)
{
	/* Should only be applied to RTE_RESULT base relations */
	Assert(rel->relid > 0);
	Assert(planner_rt_fetch(rel->relid, root)->rtekind == RTE_RESULT);

	/* RTE_RESULT always generates a single row, natively */
	rel->tuples = 1;

	/* Now estimate number of output rows, etc */
	set_baserel_size_estimates(root, rel);
}