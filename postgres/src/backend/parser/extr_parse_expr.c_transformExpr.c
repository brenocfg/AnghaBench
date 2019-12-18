#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ p_expr_kind; } ;
typedef  TYPE_1__ ParseState ;
typedef  scalar_t__ ParseExprKind ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EXPR_KIND_NONE ; 
 int /*<<< orphan*/ * transformExprRecurse (TYPE_1__*,int /*<<< orphan*/ *) ; 

Node *
transformExpr(ParseState *pstate, Node *expr, ParseExprKind exprKind)
{
	Node	   *result;
	ParseExprKind sv_expr_kind;

	/* Save and restore identity of expression type we're parsing */
	Assert(exprKind != EXPR_KIND_NONE);
	sv_expr_kind = pstate->p_expr_kind;
	pstate->p_expr_kind = exprKind;

	result = transformExprRecurse(pstate, expr);

	pstate->p_expr_kind = sv_expr_kind;

	return result;
}