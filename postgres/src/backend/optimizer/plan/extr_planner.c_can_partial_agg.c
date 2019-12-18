#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hasNonSerial; scalar_t__ hasNonPartial; } ;
struct TYPE_7__ {TYPE_1__* parse; } ;
struct TYPE_6__ {scalar_t__ groupClause; scalar_t__ groupingSets; int /*<<< orphan*/  hasAggs; } ;
typedef  TYPE_1__ Query ;
typedef  TYPE_2__ PlannerInfo ;
typedef  TYPE_3__ AggClauseCosts ;

/* Variables and functions */
 scalar_t__ NIL ; 

__attribute__((used)) static bool
can_partial_agg(PlannerInfo *root, const AggClauseCosts *agg_costs)
{
	Query	   *parse = root->parse;

	if (!parse->hasAggs && parse->groupClause == NIL)
	{
		/*
		 * We don't know how to do parallel aggregation unless we have either
		 * some aggregates or a grouping clause.
		 */
		return false;
	}
	else if (parse->groupingSets)
	{
		/* We don't know how to do grouping sets in parallel. */
		return false;
	}
	else if (agg_costs->hasNonPartial || agg_costs->hasNonSerial)
	{
		/* Insufficient support for partial mode. */
		return false;
	}

	/* Everything looks good. */
	return true;
}