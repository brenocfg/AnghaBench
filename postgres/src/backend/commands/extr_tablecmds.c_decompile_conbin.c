#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_2__ {int /*<<< orphan*/  conrelid; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_constraint_conbin ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pg_get_expr ; 

__attribute__((used)) static char *
decompile_conbin(HeapTuple contup, TupleDesc tupdesc)
{
	Form_pg_constraint con;
	bool		isnull;
	Datum		attr;
	Datum		expr;

	con = (Form_pg_constraint) GETSTRUCT(contup);
	attr = heap_getattr(contup, Anum_pg_constraint_conbin, tupdesc, &isnull);
	if (isnull)
		elog(ERROR, "null conbin for constraint %u", con->oid);

	expr = DirectFunctionCall2(pg_get_expr, attr,
							   ObjectIdGetDatum(con->conrelid));
	return TextDatumGetCString(expr);
}