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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 scalar_t__ makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_agg_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
build_aggregate_finalfn_expr(Oid *agg_input_types,
							 int num_finalfn_inputs,
							 Oid agg_state_type,
							 Oid agg_result_type,
							 Oid agg_input_collation,
							 Oid finalfn_oid,
							 Expr **finalfnexpr)
{
	List	   *args;
	int			i;

	/*
	 * Build expr tree for final function
	 */
	args = list_make1(make_agg_arg(agg_state_type, agg_input_collation));

	/* finalfn may take additional args, which match agg's input types */
	for (i = 0; i < num_finalfn_inputs - 1; i++)
	{
		args = lappend(args,
					   make_agg_arg(agg_input_types[i], agg_input_collation));
	}

	*finalfnexpr = (Expr *) makeFuncExpr(finalfn_oid,
										 agg_result_type,
										 args,
										 InvalidOid,
										 agg_input_collation,
										 COERCE_EXPLICIT_CALL);
	/* finalfn is currently never treated as variadic */
}