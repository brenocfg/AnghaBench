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
struct TYPE_7__ {int p_next_resno; scalar_t__ p_resolve_unknowns; } ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_RETURNING ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  exprLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markTargetListOrigins (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolveTargetListUnknowns (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transformTargetList (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
transformReturningList(ParseState *pstate, List *returningList)
{
	List	   *rlist;
	int			save_next_resno;

	if (returningList == NIL)
		return NIL;				/* nothing to do */

	/*
	 * We need to assign resnos starting at one in the RETURNING list. Save
	 * and restore the main tlist's value of p_next_resno, just in case
	 * someone looks at it later (probably won't happen).
	 */
	save_next_resno = pstate->p_next_resno;
	pstate->p_next_resno = 1;

	/* transform RETURNING identically to a SELECT targetlist */
	rlist = transformTargetList(pstate, returningList, EXPR_KIND_RETURNING);

	/*
	 * Complain if the nonempty tlist expanded to nothing (which is possible
	 * if it contains only a star-expansion of a zero-column table).  If we
	 * allow this, the parsed Query will look like it didn't have RETURNING,
	 * with results that would probably surprise the user.
	 */
	if (rlist == NIL)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("RETURNING must have at least one column"),
				 parser_errposition(pstate,
									exprLocation(linitial(returningList)))));

	/* mark column origins */
	markTargetListOrigins(pstate, rlist);

	/* resolve any still-unresolved output columns as being type text */
	if (pstate->p_resolve_unknowns)
		resolveTargetListUnknowns(pstate, rlist);

	/* restore state */
	pstate->p_next_resno = save_next_resno;

	return rlist;
}