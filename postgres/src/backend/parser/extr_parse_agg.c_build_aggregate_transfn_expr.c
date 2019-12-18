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
struct TYPE_3__ {int funcvariadic; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ FuncExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_agg_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
build_aggregate_transfn_expr(Oid *agg_input_types,
							 int agg_num_inputs,
							 int agg_num_direct_inputs,
							 bool agg_variadic,
							 Oid agg_state_type,
							 Oid agg_input_collation,
							 Oid transfn_oid,
							 Oid invtransfn_oid,
							 Expr **transfnexpr,
							 Expr **invtransfnexpr)
{
	List	   *args;
	FuncExpr   *fexpr;
	int			i;

	/*
	 * Build arg list to use in the transfn FuncExpr node.
	 */
	args = list_make1(make_agg_arg(agg_state_type, agg_input_collation));

	for (i = agg_num_direct_inputs; i < agg_num_inputs; i++)
	{
		args = lappend(args,
					   make_agg_arg(agg_input_types[i], agg_input_collation));
	}

	fexpr = makeFuncExpr(transfn_oid,
						 agg_state_type,
						 args,
						 InvalidOid,
						 agg_input_collation,
						 COERCE_EXPLICIT_CALL);
	fexpr->funcvariadic = agg_variadic;
	*transfnexpr = (Expr *) fexpr;

	/*
	 * Build invtransfn expression if requested, with same args as transfn
	 */
	if (invtransfnexpr != NULL)
	{
		if (OidIsValid(invtransfn_oid))
		{
			fexpr = makeFuncExpr(invtransfn_oid,
								 agg_state_type,
								 args,
								 InvalidOid,
								 agg_input_collation,
								 COERCE_EXPLICIT_CALL);
			fexpr->funcvariadic = agg_variadic;
			*invtransfnexpr = (Expr *) fexpr;
		}
		else
			*invtransfnexpr = NULL;
	}
}