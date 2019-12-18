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
struct TYPE_2__ {int /*<<< orphan*/  tmplname; int /*<<< orphan*/  tmplinit; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_ts_template ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSTEMPLATEOID ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_dictoptions(Oid tmplId, List *dictoptions)
{
	HeapTuple	tup;
	Form_pg_ts_template tform;
	Oid			initmethod;

	/*
	 * Suppress this test when running in a standalone backend.  This is a
	 * hack to allow initdb to create prefab dictionaries that might not
	 * actually be usable in template1's encoding (due to using external files
	 * that can't be translated into template1's encoding).  We want to create
	 * them anyway, since they might be usable later in other databases.
	 */
	if (!IsUnderPostmaster)
		return;

	tup = SearchSysCache1(TSTEMPLATEOID, ObjectIdGetDatum(tmplId));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for text search template %u",
			 tmplId);
	tform = (Form_pg_ts_template) GETSTRUCT(tup);

	initmethod = tform->tmplinit;

	if (!OidIsValid(initmethod))
	{
		/* If there is no init method, disallow any options */
		if (dictoptions)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("text search template \"%s\" does not accept options",
							NameStr(tform->tmplname))));
	}
	else
	{
		/*
		 * Copy the options just in case init method thinks it can scribble on
		 * them ...
		 */
		dictoptions = copyObject(dictoptions);

		/*
		 * Call the init method and see if it complains.  We don't worry about
		 * it leaking memory, since our command will soon be over anyway.
		 */
		(void) OidFunctionCall1(initmethod, PointerGetDatum(dictoptions));
	}

	ReleaseSysCache(tup);
}