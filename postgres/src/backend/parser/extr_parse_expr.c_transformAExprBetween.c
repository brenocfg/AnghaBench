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
struct TYPE_3__ {int kind; int /*<<< orphan*/  location; int /*<<< orphan*/  rexpr; int /*<<< orphan*/ * lexpr; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ A_Expr ;

/* Variables and functions */
#define  AEXPR_BETWEEN 131 
#define  AEXPR_BETWEEN_SYM 130 
#define  AEXPR_NOT_BETWEEN 129 
#define  AEXPR_NOT_BETWEEN_SYM 128 
 int /*<<< orphan*/  AEXPR_OP ; 
 int /*<<< orphan*/  AEXPR_PAREN ; 
 int /*<<< orphan*/  AND_EXPR ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int List ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  OR_EXPR ; 
 int args ; 
 int /*<<< orphan*/  castNode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  emit_precedence_warnings (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int) ; 
 int list_length (int) ; 
 int list_make2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lsecond (int) ; 
 scalar_t__ makeA_Expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ makeBoolExpr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeSimpleA_Expr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int operator_precedence_group (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ operator_precedence_warning ; 
 int /*<<< orphan*/ * transformExprRecurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *
transformAExprBetween(ParseState *pstate, A_Expr *a)
{
	Node	   *aexpr;
	Node	   *bexpr;
	Node	   *cexpr;
	Node	   *result;
	Node	   *sub1;
	Node	   *sub2;
	List	   *args;

	/* Deconstruct A_Expr into three subexprs */
	aexpr = a->lexpr;
	args = castNode(List, a->rexpr);
	Assert(list_length(args) == 2);
	bexpr = (Node *) linitial(args);
	cexpr = (Node *) lsecond(args);

	if (operator_precedence_warning)
	{
		int			opgroup;
		const char *opname;

		opgroup = operator_precedence_group((Node *) a, &opname);
		emit_precedence_warnings(pstate, opgroup, opname,
								 aexpr, cexpr,
								 a->location);
		/* We can ignore bexpr thanks to syntactic restrictions */
		/* Wrap subexpressions to prevent extra warnings */
		aexpr = (Node *) makeA_Expr(AEXPR_PAREN, NIL, aexpr, NULL, -1);
		bexpr = (Node *) makeA_Expr(AEXPR_PAREN, NIL, bexpr, NULL, -1);
		cexpr = (Node *) makeA_Expr(AEXPR_PAREN, NIL, cexpr, NULL, -1);
	}

	/*
	 * Build the equivalent comparison expression.  Make copies of
	 * multiply-referenced subexpressions for safety.  (XXX this is really
	 * wrong since it results in multiple runtime evaluations of what may be
	 * volatile expressions ...)
	 *
	 * Ideally we would not use hard-wired operators here but instead use
	 * opclasses.  However, mixed data types and other issues make this
	 * difficult:
	 * http://archives.postgresql.org/pgsql-hackers/2008-08/msg01142.php
	 */
	switch (a->kind)
	{
		case AEXPR_BETWEEN:
			args = list_make2(makeSimpleA_Expr(AEXPR_OP, ">=",
											   aexpr, bexpr,
											   a->location),
							  makeSimpleA_Expr(AEXPR_OP, "<=",
											   copyObject(aexpr), cexpr,
											   a->location));
			result = (Node *) makeBoolExpr(AND_EXPR, args, a->location);
			break;
		case AEXPR_NOT_BETWEEN:
			args = list_make2(makeSimpleA_Expr(AEXPR_OP, "<",
											   aexpr, bexpr,
											   a->location),
							  makeSimpleA_Expr(AEXPR_OP, ">",
											   copyObject(aexpr), cexpr,
											   a->location));
			result = (Node *) makeBoolExpr(OR_EXPR, args, a->location);
			break;
		case AEXPR_BETWEEN_SYM:
			args = list_make2(makeSimpleA_Expr(AEXPR_OP, ">=",
											   aexpr, bexpr,
											   a->location),
							  makeSimpleA_Expr(AEXPR_OP, "<=",
											   copyObject(aexpr), cexpr,
											   a->location));
			sub1 = (Node *) makeBoolExpr(AND_EXPR, args, a->location);
			args = list_make2(makeSimpleA_Expr(AEXPR_OP, ">=",
											   copyObject(aexpr), copyObject(cexpr),
											   a->location),
							  makeSimpleA_Expr(AEXPR_OP, "<=",
											   copyObject(aexpr), copyObject(bexpr),
											   a->location));
			sub2 = (Node *) makeBoolExpr(AND_EXPR, args, a->location);
			args = list_make2(sub1, sub2);
			result = (Node *) makeBoolExpr(OR_EXPR, args, a->location);
			break;
		case AEXPR_NOT_BETWEEN_SYM:
			args = list_make2(makeSimpleA_Expr(AEXPR_OP, "<",
											   aexpr, bexpr,
											   a->location),
							  makeSimpleA_Expr(AEXPR_OP, ">",
											   copyObject(aexpr), cexpr,
											   a->location));
			sub1 = (Node *) makeBoolExpr(OR_EXPR, args, a->location);
			args = list_make2(makeSimpleA_Expr(AEXPR_OP, "<",
											   copyObject(aexpr), copyObject(cexpr),
											   a->location),
							  makeSimpleA_Expr(AEXPR_OP, ">",
											   copyObject(aexpr), copyObject(bexpr),
											   a->location));
			sub2 = (Node *) makeBoolExpr(OR_EXPR, args, a->location);
			args = list_make2(sub1, sub2);
			result = (Node *) makeBoolExpr(AND_EXPR, args, a->location);
			break;
		default:
			elog(ERROR, "unrecognized A_Expr kind: %d", a->kind);
			result = NULL;		/* keep compiler quiet */
			break;
	}

	return transformExprRecurse(pstate, result);
}