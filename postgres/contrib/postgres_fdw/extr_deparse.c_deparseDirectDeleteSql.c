#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ ** params_list; int /*<<< orphan*/  buf; TYPE_2__* scanrel; TYPE_2__* foreignrel; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ deparse_expr_cxt ;
struct TYPE_8__ {scalar_t__ reloptkind; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RELOPT_JOINREL ; 
 int /*<<< orphan*/  REL_ALIAS_PREFIX ; 
 int /*<<< orphan*/  appendConditions (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  deparseExplicitTargetList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  deparseFromExprForRel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  deparseRelation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deparseReturningList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  planner_rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
deparseDirectDeleteSql(StringInfo buf, PlannerInfo *root,
					   Index rtindex, Relation rel,
					   RelOptInfo *foreignrel,
					   List *remote_conds,
					   List **params_list,
					   List *returningList,
					   List **retrieved_attrs)
{
	deparse_expr_cxt context;

	/* Set up context struct for recursion */
	context.root = root;
	context.foreignrel = foreignrel;
	context.scanrel = foreignrel;
	context.buf = buf;
	context.params_list = params_list;

	appendStringInfoString(buf, "DELETE FROM ");
	deparseRelation(buf, rel);
	if (foreignrel->reloptkind == RELOPT_JOINREL)
		appendStringInfo(buf, " %s%d", REL_ALIAS_PREFIX, rtindex);

	if (foreignrel->reloptkind == RELOPT_JOINREL)
	{
		List	   *ignore_conds = NIL;

		appendStringInfoString(buf, " USING ");
		deparseFromExprForRel(buf, root, foreignrel, true, rtindex,
							  &ignore_conds, params_list);
		remote_conds = list_concat(remote_conds, ignore_conds);
	}

	if (remote_conds)
	{
		appendStringInfoString(buf, " WHERE ");
		appendConditions(remote_conds, &context);
	}

	if (foreignrel->reloptkind == RELOPT_JOINREL)
		deparseExplicitTargetList(returningList, true, retrieved_attrs,
								  &context);
	else
		deparseReturningList(buf, planner_rt_fetch(rtindex, root),
							 rtindex, rel, false,
							 NIL, returningList, retrieved_attrs);
}