#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  indentLevel; int /*<<< orphan*/  buf; } ;
typedef  TYPE_3__ deparse_context ;
struct TYPE_25__ {scalar_t__ returningList; TYPE_2__* jointree; int /*<<< orphan*/  targetList; int /*<<< orphan*/  rtable; int /*<<< orphan*/  resultRelation; } ;
struct TYPE_24__ {scalar_t__ rtekind; TYPE_1__* alias; int /*<<< orphan*/  relid; } ;
struct TYPE_22__ {int /*<<< orphan*/ * quals; } ;
struct TYPE_21__ {int /*<<< orphan*/  aliasname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_4__ RangeTblEntry ;
typedef  TYPE_5__ Query ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  PRETTYINDENT_STD ; 
 scalar_t__ PRETTY_INDENT (TYPE_3__*) ; 
 scalar_t__ RTE_RELATION ; 
 int /*<<< orphan*/  appendContextKeyword (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generate_relation_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_from_clause (TYPE_5__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  get_rule_expr (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  get_target_list (scalar_t__,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_update_query_targetlist_def (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  get_with_clause (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  only_marker (TYPE_4__*) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 
 TYPE_4__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_update_query_def(Query *query, deparse_context *context)
{
	StringInfo	buf = context->buf;
	RangeTblEntry *rte;

	/* Insert the WITH clause if given */
	get_with_clause(query, context);

	/*
	 * Start the query with UPDATE relname SET
	 */
	rte = rt_fetch(query->resultRelation, query->rtable);
	Assert(rte->rtekind == RTE_RELATION);
	if (PRETTY_INDENT(context))
	{
		appendStringInfoChar(buf, ' ');
		context->indentLevel += PRETTYINDENT_STD;
	}
	appendStringInfo(buf, "UPDATE %s%s",
					 only_marker(rte),
					 generate_relation_name(rte->relid, NIL));
	if (rte->alias != NULL)
		appendStringInfo(buf, " %s",
						 quote_identifier(rte->alias->aliasname));
	appendStringInfoString(buf, " SET ");

	/* Deparse targetlist */
	get_update_query_targetlist_def(query, query->targetList, context, rte);

	/* Add the FROM clause if needed */
	get_from_clause(query, " FROM ", context);

	/* Add a WHERE clause if given */
	if (query->jointree->quals != NULL)
	{
		appendContextKeyword(context, " WHERE ",
							 -PRETTYINDENT_STD, PRETTYINDENT_STD, 1);
		get_rule_expr(query->jointree->quals, context, false);
	}

	/* Add RETURNING if present */
	if (query->returningList)
	{
		appendContextKeyword(context, " RETURNING",
							 -PRETTYINDENT_STD, PRETTYINDENT_STD, 1);
		get_target_list(query->returningList, context, NULL);
	}
}