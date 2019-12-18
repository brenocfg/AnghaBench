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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {TYPE_1__* funcexpr; } ;
struct TYPE_4__ {int /*<<< orphan*/  funcid; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ FuncExpr ;
typedef  TYPE_2__ CallStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_result_tupdesc_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

TupleDesc
CallStmtResultDesc(CallStmt *stmt)
{
	FuncExpr   *fexpr;
	HeapTuple	tuple;
	TupleDesc	tupdesc;

	fexpr = stmt->funcexpr;

	tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(fexpr->funcid));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for procedure %u", fexpr->funcid);

	tupdesc = build_function_result_tupdesc_t(tuple);

	ReleaseSysCache(tuple);

	return tupdesc;
}