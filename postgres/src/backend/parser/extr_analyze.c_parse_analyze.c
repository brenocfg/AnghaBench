#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* p_sourcetext; int /*<<< orphan*/ * p_queryEnv; } ;
typedef  int /*<<< orphan*/  RawStmt ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_parsestate (TYPE_1__*) ; 
 TYPE_1__* make_parsestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_fixed_parameters (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  post_parse_analyze_hook (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transformTopLevelStmt (TYPE_1__*,int /*<<< orphan*/ *) ; 

Query *
parse_analyze(RawStmt *parseTree, const char *sourceText,
			  Oid *paramTypes, int numParams,
			  QueryEnvironment *queryEnv)
{
	ParseState *pstate = make_parsestate(NULL);
	Query	   *query;

	Assert(sourceText != NULL); /* required as of 8.4 */

	pstate->p_sourcetext = sourceText;

	if (numParams > 0)
		parse_fixed_parameters(pstate, paramTypes, numParams);

	pstate->p_queryEnv = queryEnv;

	query = transformTopLevelStmt(pstate, parseTree);

	if (post_parse_analyze_hook)
		(*post_parse_analyze_hook) (pstate, query);

	free_parsestate(pstate);

	return query;
}