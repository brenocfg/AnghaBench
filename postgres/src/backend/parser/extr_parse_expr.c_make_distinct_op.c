#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ opresulttype; scalar_t__ opretset; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_last_srf; } ;
typedef  TYPE_1__ ParseState ;
typedef  TYPE_2__ OpExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ BOOLOID ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NodeSetTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_DistinctExpr ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * make_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int) ; 

__attribute__((used)) static Expr *
make_distinct_op(ParseState *pstate, List *opname, Node *ltree, Node *rtree,
				 int location)
{
	Expr	   *result;

	result = make_op(pstate, opname, ltree, rtree,
					 pstate->p_last_srf, location);
	if (((OpExpr *) result)->opresulttype != BOOLOID)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("IS DISTINCT FROM requires = operator to yield boolean"),
				 parser_errposition(pstate, location)));
	if (((OpExpr *) result)->opretset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
		/* translator: %s is name of a SQL construct, eg NULLIF */
				 errmsg("%s must not return a set", "IS DISTINCT FROM"),
				 parser_errposition(pstate, location)));

	/*
	 * We rely on DistinctExpr and OpExpr being same struct
	 */
	NodeSetTag(result, T_DistinctExpr);

	return result;
}