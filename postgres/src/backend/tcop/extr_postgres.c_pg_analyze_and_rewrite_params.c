#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char const* p_sourcetext; int /*<<< orphan*/ * p_queryEnv; } ;
typedef  int /*<<< orphan*/  RawStmt ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  (* ParserSetupHook ) (TYPE_1__*,void*) ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_QUERY_REWRITE_DONE (char const*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_QUERY_REWRITE_START (char const*) ; 
 int /*<<< orphan*/  free_parsestate (TYPE_1__*) ; 
 scalar_t__ log_parser_stats ; 
 TYPE_1__* make_parsestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_rewrite_query (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_parse_analyze_hook (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transformTopLevelStmt (TYPE_1__*,int /*<<< orphan*/ *) ; 

List *
pg_analyze_and_rewrite_params(RawStmt *parsetree,
							  const char *query_string,
							  ParserSetupHook parserSetup,
							  void *parserSetupArg,
							  QueryEnvironment *queryEnv)
{
	ParseState *pstate;
	Query	   *query;
	List	   *querytree_list;

	Assert(query_string != NULL);	/* required as of 8.4 */

	TRACE_POSTGRESQL_QUERY_REWRITE_START(query_string);

	/*
	 * (1) Perform parse analysis.
	 */
	if (log_parser_stats)
		ResetUsage();

	pstate = make_parsestate(NULL);
	pstate->p_sourcetext = query_string;
	pstate->p_queryEnv = queryEnv;
	(*parserSetup) (pstate, parserSetupArg);

	query = transformTopLevelStmt(pstate, parsetree);

	if (post_parse_analyze_hook)
		(*post_parse_analyze_hook) (pstate, query);

	free_parsestate(pstate);

	if (log_parser_stats)
		ShowUsage("PARSE ANALYSIS STATISTICS");

	/*
	 * (2) Rewrite the queries, as necessary
	 */
	querytree_list = pg_rewrite_query(query);

	TRACE_POSTGRESQL_QUERY_REWRITE_DONE(query_string);

	return querytree_list;
}