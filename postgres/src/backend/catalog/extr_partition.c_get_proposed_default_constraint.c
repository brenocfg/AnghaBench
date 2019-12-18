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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_EXPR ; 
 int /*<<< orphan*/ * canonicalize_qual (int /*<<< orphan*/ *,int) ; 
 scalar_t__ eval_const_expressions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeBoolExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * make_ands_explicit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_ands_implicit (int /*<<< orphan*/ *) ; 

List *
get_proposed_default_constraint(List *new_part_constraints)
{
	Expr	   *defPartConstraint;

	defPartConstraint = make_ands_explicit(new_part_constraints);

	/*
	 * Derive the partition constraints of default partition by negating the
	 * given partition constraints. The partition constraint never evaluates
	 * to NULL, so negating it like this is safe.
	 */
	defPartConstraint = makeBoolExpr(NOT_EXPR,
									 list_make1(defPartConstraint),
									 -1);

	/* Simplify, to put the negated expression into canonical form */
	defPartConstraint =
		(Expr *) eval_const_expressions(NULL,
										(Node *) defPartConstraint);
	defPartConstraint = canonicalize_qual(defPartConstraint, true);

	return make_ands_implicit(defPartConstraint);
}