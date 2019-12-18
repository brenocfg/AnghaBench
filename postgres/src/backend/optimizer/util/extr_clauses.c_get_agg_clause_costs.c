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
struct TYPE_3__ {int /*<<< orphan*/ * costs; int /*<<< orphan*/  aggsplit; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ get_agg_clause_costs_context ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  AggSplit ;
typedef  int /*<<< orphan*/  AggClauseCosts ;

/* Variables and functions */
 int /*<<< orphan*/  get_agg_clause_costs_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
get_agg_clause_costs(PlannerInfo *root, Node *clause, AggSplit aggsplit,
					 AggClauseCosts *costs)
{
	get_agg_clause_costs_context context;

	context.root = root;
	context.aggsplit = aggsplit;
	context.costs = costs;
	(void) get_agg_clause_costs_walker(clause, &context);
}