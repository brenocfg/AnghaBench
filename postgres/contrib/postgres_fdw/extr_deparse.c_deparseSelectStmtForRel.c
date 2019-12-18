#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ ** params_list; TYPE_2__* scanrel; TYPE_2__* foreignrel; int /*<<< orphan*/ * root; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_expr_cxt ;
struct TYPE_17__ {int /*<<< orphan*/ * remote_conds; TYPE_2__* outerrel; } ;
struct TYPE_16__ {scalar_t__ fdw_private; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ PgFdwRelationInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IS_JOIN_REL (TYPE_2__*) ; 
 scalar_t__ IS_SIMPLE_REL (TYPE_2__*) ; 
 scalar_t__ IS_UPPER_REL (TYPE_2__*) ; 
 int /*<<< orphan*/  appendConditions (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  appendGroupByClause (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  appendLimitClause (TYPE_1__*) ; 
 int /*<<< orphan*/  appendOrderByClause (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  deparseFromExpr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  deparseLockingClause (TYPE_1__*) ; 
 int /*<<< orphan*/  deparseSelectSql (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,TYPE_1__*) ; 

void
deparseSelectStmtForRel(StringInfo buf, PlannerInfo *root, RelOptInfo *rel,
						List *tlist, List *remote_conds, List *pathkeys,
						bool has_final_sort, bool has_limit, bool is_subquery,
						List **retrieved_attrs, List **params_list)
{
	deparse_expr_cxt context;
	PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) rel->fdw_private;
	List	   *quals;

	/*
	 * We handle relations for foreign tables, joins between those and upper
	 * relations.
	 */
	Assert(IS_JOIN_REL(rel) || IS_SIMPLE_REL(rel) || IS_UPPER_REL(rel));

	/* Fill portions of context common to upper, join and base relation */
	context.buf = buf;
	context.root = root;
	context.foreignrel = rel;
	context.scanrel = IS_UPPER_REL(rel) ? fpinfo->outerrel : rel;
	context.params_list = params_list;

	/* Construct SELECT clause */
	deparseSelectSql(tlist, is_subquery, retrieved_attrs, &context);

	/*
	 * For upper relations, the WHERE clause is built from the remote
	 * conditions of the underlying scan relation; otherwise, we can use the
	 * supplied list of remote conditions directly.
	 */
	if (IS_UPPER_REL(rel))
	{
		PgFdwRelationInfo *ofpinfo;

		ofpinfo = (PgFdwRelationInfo *) fpinfo->outerrel->fdw_private;
		quals = ofpinfo->remote_conds;
	}
	else
		quals = remote_conds;

	/* Construct FROM and WHERE clauses */
	deparseFromExpr(quals, &context);

	if (IS_UPPER_REL(rel))
	{
		/* Append GROUP BY clause */
		appendGroupByClause(tlist, &context);

		/* Append HAVING clause */
		if (remote_conds)
		{
			appendStringInfoString(buf, " HAVING ");
			appendConditions(remote_conds, &context);
		}
	}

	/* Add ORDER BY clause if we found any useful pathkeys */
	if (pathkeys)
		appendOrderByClause(pathkeys, has_final_sort, &context);

	/* Add LIMIT clause if necessary */
	if (has_limit)
		appendLimitClause(&context);

	/* Add any necessary FOR UPDATE/SHARE. */
	deparseLockingClause(&context);
}