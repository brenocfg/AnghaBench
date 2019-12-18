#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  location; int /*<<< orphan*/  name; int /*<<< orphan*/  rexpr; int /*<<< orphan*/  lexpr; } ;
struct TYPE_11__ {scalar_t__ opresulttype; int /*<<< orphan*/  args; scalar_t__ opretset; } ;
struct TYPE_10__ {int /*<<< orphan*/  p_last_srf; } ;
typedef  TYPE_1__ ParseState ;
typedef  TYPE_2__ OpExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ A_Expr ;

/* Variables and functions */
 scalar_t__ BOOLOID ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NodeSetTag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_NullIfExpr ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 scalar_t__ make_op (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformExprRecurse (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
transformAExprNullIf(ParseState *pstate, A_Expr *a)
{
	Node	   *lexpr = transformExprRecurse(pstate, a->lexpr);
	Node	   *rexpr = transformExprRecurse(pstate, a->rexpr);
	OpExpr	   *result;

	result = (OpExpr *) make_op(pstate,
								a->name,
								lexpr,
								rexpr,
								pstate->p_last_srf,
								a->location);

	/*
	 * The comparison operator itself should yield boolean ...
	 */
	if (result->opresulttype != BOOLOID)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("NULLIF requires = operator to yield boolean"),
				 parser_errposition(pstate, a->location)));
	if (result->opretset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
		/* translator: %s is name of a SQL construct, eg NULLIF */
				 errmsg("%s must not return a set", "NULLIF"),
				 parser_errposition(pstate, a->location)));

	/*
	 * ... but the NullIfExpr will yield the first operand's type.
	 */
	result->opresulttype = exprType((Node *) linitial(result->args));

	/*
	 * We rely on NullIfExpr and OpExpr being the same struct
	 */
	NodeSetTag(result, T_NullIfExpr);

	return (Node *) result;
}