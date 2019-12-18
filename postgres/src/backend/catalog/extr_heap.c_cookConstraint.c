#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_rtable; } ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_COLUMN_REFERENCE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_CHECK_CONSTRAINT ; 
 int /*<<< orphan*/  assign_expr_collations (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * coerce_to_boolean (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformExpr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
cookConstraint(ParseState *pstate,
			   Node *raw_constraint,
			   char *relname)
{
	Node	   *expr;

	/*
	 * Transform raw parsetree to executable expression.
	 */
	expr = transformExpr(pstate, raw_constraint, EXPR_KIND_CHECK_CONSTRAINT);

	/*
	 * Make sure it yields a boolean result.
	 */
	expr = coerce_to_boolean(pstate, expr, "CHECK");

	/*
	 * Take care of collations.
	 */
	assign_expr_collations(pstate, expr);

	/*
	 * Make sure no outside relations are referred to (this is probably dead
	 * code now that add_missing_from is history).
	 */
	if (list_length(pstate->p_rtable) != 1)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
				 errmsg("only table \"%s\" can be referenced in check constraint",
						relname)));

	return expr;
}