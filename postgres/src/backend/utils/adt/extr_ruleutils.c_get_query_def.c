#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  deparse_namespace ;
struct TYPE_16__ {int varprefix; int prettyFlags; int wrapColumn; int indentLevel; int /*<<< orphan*/  special_exprkind; int /*<<< orphan*/ * windowTList; int /*<<< orphan*/ * windowClause; int /*<<< orphan*/  namespaces; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_context ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_17__ {int commandType; int /*<<< orphan*/  rtable; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireRewriteLocks (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
#define  CMD_DELETE 133 
#define  CMD_INSERT 132 
#define  CMD_NOTHING 131 
#define  CMD_SELECT 130 
#define  CMD_UPDATE 129 
#define  CMD_UTILITY 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_NONE ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_delete_query_def (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_insert_query_def (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_select_query_def (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_update_query_def (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  get_utility_query_def (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lcons (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_deparse_for_query (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_query_def(Query *query, StringInfo buf, List *parentnamespace,
			  TupleDesc resultDesc,
			  int prettyFlags, int wrapColumn, int startIndent)
{
	deparse_context context;
	deparse_namespace dpns;

	/* Guard against excessively long or deeply-nested queries */
	CHECK_FOR_INTERRUPTS();
	check_stack_depth();

	/*
	 * Before we begin to examine the query, acquire locks on referenced
	 * relations, and fix up deleted columns in JOIN RTEs.  This ensures
	 * consistent results.  Note we assume it's OK to scribble on the passed
	 * querytree!
	 *
	 * We are only deparsing the query (we are not about to execute it), so we
	 * only need AccessShareLock on the relations it mentions.
	 */
	AcquireRewriteLocks(query, false, false);

	context.buf = buf;
	context.namespaces = lcons(&dpns, list_copy(parentnamespace));
	context.windowClause = NIL;
	context.windowTList = NIL;
	context.varprefix = (parentnamespace != NIL ||
						 list_length(query->rtable) != 1);
	context.prettyFlags = prettyFlags;
	context.wrapColumn = wrapColumn;
	context.indentLevel = startIndent;
	context.special_exprkind = EXPR_KIND_NONE;

	set_deparse_for_query(&dpns, query, parentnamespace);

	switch (query->commandType)
	{
		case CMD_SELECT:
			get_select_query_def(query, &context, resultDesc);
			break;

		case CMD_UPDATE:
			get_update_query_def(query, &context);
			break;

		case CMD_INSERT:
			get_insert_query_def(query, &context);
			break;

		case CMD_DELETE:
			get_delete_query_def(query, &context);
			break;

		case CMD_NOTHING:
			appendStringInfoString(buf, "NOTHING");
			break;

		case CMD_UTILITY:
			get_utility_query_def(query, &context);
			break;

		default:
			elog(ERROR, "unrecognized query command type: %d",
				 query->commandType);
			break;
	}
}