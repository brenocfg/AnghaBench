#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RawStmt ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_QUERY_REWRITE_DONE (char const*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_QUERY_REWRITE_START (char const*) ; 
 scalar_t__ log_parser_stats ; 
 int /*<<< orphan*/ * parse_analyze (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_rewrite_query (int /*<<< orphan*/ *) ; 

List *
pg_analyze_and_rewrite(RawStmt *parsetree, const char *query_string,
					   Oid *paramTypes, int numParams,
					   QueryEnvironment *queryEnv)
{
	Query	   *query;
	List	   *querytree_list;

	TRACE_POSTGRESQL_QUERY_REWRITE_START(query_string);

	/*
	 * (1) Perform parse analysis.
	 */
	if (log_parser_stats)
		ResetUsage();

	query = parse_analyze(parsetree, query_string, paramTypes, numParams,
						  queryEnv);

	if (log_parser_stats)
		ShowUsage("PARSE ANALYSIS STATISTICS");

	/*
	 * (2) Rewrite the queries, as necessary
	 */
	querytree_list = pg_rewrite_query(query);

	TRACE_POSTGRESQL_QUERY_REWRITE_DONE(query_string);

	return querytree_list;
}