#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ commandType; int /*<<< orphan*/  hasSubLinks; TYPE_1__* jointree; int /*<<< orphan*/ * setOperations; scalar_t__ utilityStmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  quals; } ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_UTILITY ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsA (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotifyStmt ; 
 int /*<<< orphan*/  checkExprHasSubLink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  contain_aggs_of_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  make_and_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
AddQual(Query *parsetree, Node *qual)
{
	Node	   *copy;

	if (qual == NULL)
		return;

	if (parsetree->commandType == CMD_UTILITY)
	{
		/*
		 * There's noplace to put the qual on a utility statement.
		 *
		 * If it's a NOTIFY, silently ignore the qual; this means that the
		 * NOTIFY will execute, whether or not there are any qualifying rows.
		 * While clearly wrong, this is much more useful than refusing to
		 * execute the rule at all, and extra NOTIFY events are harmless for
		 * typical uses of NOTIFY.
		 *
		 * If it isn't a NOTIFY, error out, since unconditional execution of
		 * other utility stmts is unlikely to be wanted.  (This case is not
		 * currently allowed anyway, but keep the test for safety.)
		 */
		if (parsetree->utilityStmt && IsA(parsetree->utilityStmt, NotifyStmt))
			return;
		else
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("conditional utility statements are not implemented")));
	}

	if (parsetree->setOperations != NULL)
	{
		/*
		 * There's noplace to put the qual on a setop statement, either. (This
		 * could be fixed, but right now the planner simply ignores any qual
		 * condition on a setop query.)
		 */
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("conditional UNION/INTERSECT/EXCEPT statements are not implemented")));
	}

	/* INTERSECT wants the original, but we need to copy - Jan */
	copy = copyObject(qual);

	parsetree->jointree->quals = make_and_qual(parsetree->jointree->quals,
											   copy);

	/*
	 * We had better not have stuck an aggregate into the WHERE clause.
	 */
	Assert(!contain_aggs_of_level(copy, 0));

	/*
	 * Make sure query is marked correctly if added qual has sublinks. Need
	 * not search qual when query is already marked.
	 */
	if (!parsetree->hasSubLinks)
		parsetree->hasSubLinks = checkExprHasSubLink(copy);
}