#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fn_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  lanplcallfoid; } ;
struct TYPE_6__ {int /*<<< orphan*/  prolang; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;
typedef  TYPE_2__* Form_pg_language ;
typedef  TYPE_3__ FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANGOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_cxt_security (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fmgr_info_other_lang(Oid functionId, FmgrInfo *finfo, HeapTuple procedureTuple)
{
	Form_pg_proc procedureStruct = (Form_pg_proc) GETSTRUCT(procedureTuple);
	Oid			language = procedureStruct->prolang;
	HeapTuple	languageTuple;
	Form_pg_language languageStruct;
	FmgrInfo	plfinfo;

	languageTuple = SearchSysCache1(LANGOID, ObjectIdGetDatum(language));
	if (!HeapTupleIsValid(languageTuple))
		elog(ERROR, "cache lookup failed for language %u", language);
	languageStruct = (Form_pg_language) GETSTRUCT(languageTuple);

	/*
	 * Look up the language's call handler function, ignoring any attributes
	 * that would normally cause insertion of fmgr_security_definer.  We need
	 * to get back a bare pointer to the actual C-language function.
	 */
	fmgr_info_cxt_security(languageStruct->lanplcallfoid, &plfinfo,
						   CurrentMemoryContext, true);
	finfo->fn_addr = plfinfo.fn_addr;

	ReleaseSysCache(languageTuple);
}