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
struct TYPE_2__ {int prolang; scalar_t__ prosecdef; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_proc_probin ; 
 int /*<<< orphan*/  Anum_pg_proc_proconfig ; 
 int /*<<< orphan*/  Anum_pg_proc_prosrc ; 
#define  ClanguageId 130 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FmgrHookIsNeeded (int /*<<< orphan*/ ) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
#define  INTERNALlanguageId 129 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
#define  SQLlanguageId 128 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pstrdup (char*) ; 

void
fmgr_symbol(Oid functionId, char **mod, char **fn)
{
	HeapTuple	procedureTuple;
	Form_pg_proc procedureStruct;
	bool		isnull;
	Datum		prosrcattr;
	Datum		probinattr;

	/* Otherwise we need the pg_proc entry */
	procedureTuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(functionId));
	if (!HeapTupleIsValid(procedureTuple))
		elog(ERROR, "cache lookup failed for function %u", functionId);
	procedureStruct = (Form_pg_proc) GETSTRUCT(procedureTuple);

	/*
	 */
	if (procedureStruct->prosecdef ||
		!heap_attisnull(procedureTuple, Anum_pg_proc_proconfig, NULL) ||
		FmgrHookIsNeeded(functionId))
	{
		*mod = NULL;			/* core binary */
		*fn = pstrdup("fmgr_security_definer");
		ReleaseSysCache(procedureTuple);
		return;
	}

	/* see fmgr_info_cxt_security for the individual cases */
	switch (procedureStruct->prolang)
	{
		case INTERNALlanguageId:
			prosrcattr = SysCacheGetAttr(PROCOID, procedureTuple,
										 Anum_pg_proc_prosrc, &isnull);
			if (isnull)
				elog(ERROR, "null prosrc");

			*mod = NULL;		/* core binary */
			*fn = TextDatumGetCString(prosrcattr);
			break;

		case ClanguageId:
			prosrcattr = SysCacheGetAttr(PROCOID, procedureTuple,
										 Anum_pg_proc_prosrc, &isnull);
			if (isnull)
				elog(ERROR, "null prosrc for C function %u", functionId);

			probinattr = SysCacheGetAttr(PROCOID, procedureTuple,
										 Anum_pg_proc_probin, &isnull);
			if (isnull)
				elog(ERROR, "null probin for C function %u", functionId);

			/*
			 * No need to check symbol presence / API version here, already
			 * checked in fmgr_info_cxt_security.
			 */
			*mod = TextDatumGetCString(probinattr);
			*fn = TextDatumGetCString(prosrcattr);
			break;

		case SQLlanguageId:
			*mod = NULL;		/* core binary */
			*fn = pstrdup("fmgr_sql");
			break;

		default:
			*mod = NULL;
			*fn = NULL;			/* unknown, pass pointer */
			break;
	}

	ReleaseSysCache(procedureTuple);
}