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
struct TYPE_3__ {int hasJoinRTEs; int have_non_var_grouping; int in_agg_direct_args; scalar_t__ sublevels_up; int /*<<< orphan*/ * func_grouped_rels; int /*<<< orphan*/  groupClauseCommonVars; int /*<<< orphan*/ * groupClauses; int /*<<< orphan*/ * qry; int /*<<< orphan*/ * pstate; } ;
typedef  TYPE_1__ check_ungrouped_columns_context ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  finalize_grouping_exprs_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
finalize_grouping_exprs(Node *node, ParseState *pstate, Query *qry,
						List *groupClauses, bool hasJoinRTEs,
						bool have_non_var_grouping)
{
	check_ungrouped_columns_context context;

	context.pstate = pstate;
	context.qry = qry;
	context.hasJoinRTEs = hasJoinRTEs;
	context.groupClauses = groupClauses;
	context.groupClauseCommonVars = NIL;
	context.have_non_var_grouping = have_non_var_grouping;
	context.func_grouped_rels = NULL;
	context.sublevels_up = 0;
	context.in_agg_direct_args = false;
	finalize_grouping_exprs_walker(node, &context);
}