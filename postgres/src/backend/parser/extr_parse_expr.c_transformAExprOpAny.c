#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  location; int /*<<< orphan*/  name; int /*<<< orphan*/ * rexpr; int /*<<< orphan*/ * lexpr; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ A_Expr ;

/* Variables and functions */
 int /*<<< orphan*/  PREC_GROUP_POSTFIX_OP ; 
 int /*<<< orphan*/  emit_precedence_warnings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llast (int /*<<< orphan*/ ) ; 
 scalar_t__ make_scalar_array_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ operator_precedence_warning ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformExprRecurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *
transformAExprOpAny(ParseState *pstate, A_Expr *a)
{
	Node	   *lexpr = a->lexpr;
	Node	   *rexpr = a->rexpr;

	if (operator_precedence_warning)
		emit_precedence_warnings(pstate, PREC_GROUP_POSTFIX_OP,
								 strVal(llast(a->name)),
								 lexpr, NULL,
								 a->location);

	lexpr = transformExprRecurse(pstate, lexpr);
	rexpr = transformExprRecurse(pstate, rexpr);

	return (Node *) make_scalar_array_op(pstate,
										 a->name,
										 true,
										 lexpr,
										 rexpr,
										 a->location);
}