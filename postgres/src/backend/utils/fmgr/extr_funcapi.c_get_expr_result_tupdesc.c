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
typedef  scalar_t__ TypeFuncClass ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RECORDOID ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 scalar_t__ TYPEFUNC_COMPOSITE_DOMAIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_expr_result_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

TupleDesc
get_expr_result_tupdesc(Node *expr, bool noError)
{
	TupleDesc	tupleDesc;
	TypeFuncClass functypclass;

	functypclass = get_expr_result_type(expr, NULL, &tupleDesc);

	if (functypclass == TYPEFUNC_COMPOSITE ||
		functypclass == TYPEFUNC_COMPOSITE_DOMAIN)
		return tupleDesc;

	if (!noError)
	{
		Oid			exprTypeId = exprType(expr);

		if (exprTypeId != RECORDOID)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("type %s is not composite",
							format_type_be(exprTypeId))));
		else
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("record type has not been registered")));
	}

	return NULL;
}