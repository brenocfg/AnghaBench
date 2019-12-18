#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oprcode; int /*<<< orphan*/  oprcanhash; } ;
struct TYPE_4__ {scalar_t__ opno; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ OpExpr ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_operator ;

/* Variables and functions */
 scalar_t__ ARRAY_EQ_OP ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  func_strict (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int op_hashjoinable (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
hash_ok_operator(OpExpr *expr)
{
	Oid			opid = expr->opno;

	/* quick out if not a binary operator */
	if (list_length(expr->args) != 2)
		return false;
	if (opid == ARRAY_EQ_OP)
	{
		/* array_eq is strict, but must check input type to ensure hashable */
		/* XXX record_eq will need same treatment when it becomes hashable */
		Node	   *leftarg = linitial(expr->args);

		return op_hashjoinable(opid, exprType(leftarg));
	}
	else
	{
		/* else must look up the operator properties */
		HeapTuple	tup;
		Form_pg_operator optup;

		tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(opid));
		if (!HeapTupleIsValid(tup))
			elog(ERROR, "cache lookup failed for operator %u", opid);
		optup = (Form_pg_operator) GETSTRUCT(tup);
		if (!optup->oprcanhash || !func_strict(optup->oprcode))
		{
			ReleaseSysCache(tup);
			return false;
		}
		ReleaseSysCache(tup);
		return true;
	}
}