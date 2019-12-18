#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int p_locked_from_parent; int p_resolve_unknowns; int /*<<< orphan*/ * p_parent_cte; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  CommonTableExpr ;

/* Variables and functions */
 int /*<<< orphan*/  free_parsestate (TYPE_1__*) ; 
 TYPE_1__* make_parsestate (TYPE_1__*) ; 
 int /*<<< orphan*/ * transformStmt (TYPE_1__*,int /*<<< orphan*/ *) ; 

Query *
parse_sub_analyze(Node *parseTree, ParseState *parentParseState,
				  CommonTableExpr *parentCTE,
				  bool locked_from_parent,
				  bool resolve_unknowns)
{
	ParseState *pstate = make_parsestate(parentParseState);
	Query	   *query;

	pstate->p_parent_cte = parentCTE;
	pstate->p_locked_from_parent = locked_from_parent;
	pstate->p_resolve_unknowns = resolve_unknowns;

	query = transformStmt(pstate, parseTree);

	free_parsestate(pstate);

	return query;
}