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
struct TYPE_2__ {scalar_t__ prokind; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 scalar_t__ PROKIND_AGGREGATE ; 
 scalar_t__ PROKIND_PROCEDURE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getProcedureTypeDescription(StringInfo buffer, Oid procid)
{
	HeapTuple	procTup;
	Form_pg_proc procForm;

	procTup = SearchSysCache1(PROCOID,
							  ObjectIdGetDatum(procid));
	if (!HeapTupleIsValid(procTup))
		elog(ERROR, "cache lookup failed for procedure %u", procid);
	procForm = (Form_pg_proc) GETSTRUCT(procTup);

	if (procForm->prokind == PROKIND_AGGREGATE)
		appendStringInfoString(buffer, "aggregate");
	else if (procForm->prokind == PROKIND_PROCEDURE)
		appendStringInfoString(buffer, "procedure");
	else						/* function or window function */
		appendStringInfoString(buffer, "function");

	ReleaseSysCache(procTup);
}