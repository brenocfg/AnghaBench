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
typedef  int /*<<< orphan*/  FuncExpr ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  BYTEAOID ; 
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 int /*<<< orphan*/  INTERNALOID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeFuncExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_agg_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
build_aggregate_deserialfn_expr(Oid deserialfn_oid,
								Expr **deserialfnexpr)
{
	List	   *args;
	FuncExpr   *fexpr;

	/* deserialfn always takes BYTEA, INTERNAL and returns INTERNAL */
	args = list_make2(make_agg_arg(BYTEAOID, InvalidOid),
					  make_agg_arg(INTERNALOID, InvalidOid));

	fexpr = makeFuncExpr(deserialfn_oid,
						 INTERNALOID,
						 args,
						 InvalidOid,
						 InvalidOid,
						 COERCE_EXPLICIT_CALL);
	*deserialfnexpr = (Expr *) fexpr;
}