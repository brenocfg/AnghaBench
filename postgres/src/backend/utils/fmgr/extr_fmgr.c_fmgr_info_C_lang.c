#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* inforec; int /*<<< orphan*/  user_fn; } ;
struct TYPE_9__ {int /*<<< orphan*/  fn_addr; } ;
struct TYPE_8__ {int api_version; } ;
typedef  TYPE_1__ Pg_finfo_record ;
typedef  int /*<<< orphan*/  PGFunction ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ CFuncHashTabEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_proc_probin ; 
 int /*<<< orphan*/  Anum_pg_proc_prosrc ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* fetch_finfo_record (void*,char*) ; 
 int /*<<< orphan*/  load_external_function (char*,char*,int,void**) ; 
 TYPE_3__* lookup_C_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  record_C_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*) ; 

__attribute__((used)) static void
fmgr_info_C_lang(Oid functionId, FmgrInfo *finfo, HeapTuple procedureTuple)
{
	CFuncHashTabEntry *hashentry;
	PGFunction	user_fn;
	const Pg_finfo_record *inforec;
	bool		isnull;

	/*
	 * See if we have the function address cached already
	 */
	hashentry = lookup_C_func(procedureTuple);
	if (hashentry)
	{
		user_fn = hashentry->user_fn;
		inforec = hashentry->inforec;
	}
	else
	{
		Datum		prosrcattr,
					probinattr;
		char	   *prosrcstring,
				   *probinstring;
		void	   *libraryhandle;

		/*
		 * Get prosrc and probin strings (link symbol and library filename).
		 * While in general these columns might be null, that's not allowed
		 * for C-language functions.
		 */
		prosrcattr = SysCacheGetAttr(PROCOID, procedureTuple,
									 Anum_pg_proc_prosrc, &isnull);
		if (isnull)
			elog(ERROR, "null prosrc for C function %u", functionId);
		prosrcstring = TextDatumGetCString(prosrcattr);

		probinattr = SysCacheGetAttr(PROCOID, procedureTuple,
									 Anum_pg_proc_probin, &isnull);
		if (isnull)
			elog(ERROR, "null probin for C function %u", functionId);
		probinstring = TextDatumGetCString(probinattr);

		/* Look up the function itself */
		user_fn = load_external_function(probinstring, prosrcstring, true,
										 &libraryhandle);

		/* Get the function information record (real or default) */
		inforec = fetch_finfo_record(libraryhandle, prosrcstring);

		/* Cache the addresses for later calls */
		record_C_func(procedureTuple, user_fn, inforec);

		pfree(prosrcstring);
		pfree(probinstring);
	}

	switch (inforec->api_version)
	{
		case 1:
			/* New style: call directly */
			finfo->fn_addr = user_fn;
			break;
		default:
			/* Shouldn't get here if fetch_finfo_record did its job */
			elog(ERROR, "unrecognized function API version: %d",
				 inforec->api_version);
			break;
	}
}