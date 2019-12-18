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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  FuncExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_agg_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
build_aggregate_combinefn_expr(Oid agg_state_type,
							   Oid agg_input_collation,
							   Oid combinefn_oid,
							   Expr **combinefnexpr)
{
	Node	   *argp;
	List	   *args;
	FuncExpr   *fexpr;

	/* combinefn takes two arguments of the aggregate state type */
	argp = make_agg_arg(agg_state_type, agg_input_collation);

	args = list_make2(argp, argp);

	fexpr = makeFuncExpr(combinefn_oid,
						 agg_state_type,
						 args,
						 InvalidOid,
						 agg_input_collation,
						 COERCE_EXPLICIT_CALL);
	/* combinefn is currently never treated as variadic */
	*combinefnexpr = (Expr *) fexpr;
}