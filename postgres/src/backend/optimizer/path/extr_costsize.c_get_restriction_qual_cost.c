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
struct TYPE_10__ {int /*<<< orphan*/  ppi_clauses; } ;
struct TYPE_9__ {scalar_t__ per_tuple; scalar_t__ startup; } ;
struct TYPE_8__ {TYPE_2__ baserestrictcost; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ QualCost ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ ParamPathInfo ;

/* Variables and functions */
 int /*<<< orphan*/  cost_qual_eval (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_restriction_qual_cost(PlannerInfo *root, RelOptInfo *baserel,
						  ParamPathInfo *param_info,
						  QualCost *qpqual_cost)
{
	if (param_info)
	{
		/* Include costs of pushed-down clauses */
		cost_qual_eval(qpqual_cost, param_info->ppi_clauses, root);

		qpqual_cost->startup += baserel->baserestrictcost.startup;
		qpqual_cost->per_tuple += baserel->baserestrictcost.per_tuple;
	}
	else
		*qpqual_cost = baserel->baserestrictcost;
}