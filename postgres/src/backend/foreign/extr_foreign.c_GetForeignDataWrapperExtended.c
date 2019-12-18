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
typedef  int bits16 ;
struct TYPE_5__ {int /*<<< orphan*/  options; int /*<<< orphan*/  fdwvalidator; int /*<<< orphan*/  fdwhandler; int /*<<< orphan*/  fdwname; int /*<<< orphan*/  owner; int /*<<< orphan*/  fdwid; } ;
struct TYPE_4__ {int /*<<< orphan*/  fdwvalidator; int /*<<< orphan*/  fdwhandler; int /*<<< orphan*/  fdwname; int /*<<< orphan*/  fdwowner; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_foreign_data_wrapper ;
typedef  TYPE_2__ ForeignDataWrapper ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_foreign_data_wrapper_fdwoptions ; 
 int /*<<< orphan*/  ERROR ; 
 int FDW_MISSING_OK ; 
 int /*<<< orphan*/  FOREIGNDATAWRAPPEROID ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untransformRelOptions (int /*<<< orphan*/ ) ; 

ForeignDataWrapper *
GetForeignDataWrapperExtended(Oid fdwid, bits16 flags)
{
	Form_pg_foreign_data_wrapper fdwform;
	ForeignDataWrapper *fdw;
	Datum		datum;
	HeapTuple	tp;
	bool		isnull;

	tp = SearchSysCache1(FOREIGNDATAWRAPPEROID, ObjectIdGetDatum(fdwid));

	if (!HeapTupleIsValid(tp))
	{
		if ((flags & FDW_MISSING_OK) == 0)
			elog(ERROR, "cache lookup failed for foreign-data wrapper %u", fdwid);
		return NULL;
	}

	fdwform = (Form_pg_foreign_data_wrapper) GETSTRUCT(tp);

	fdw = (ForeignDataWrapper *) palloc(sizeof(ForeignDataWrapper));
	fdw->fdwid = fdwid;
	fdw->owner = fdwform->fdwowner;
	fdw->fdwname = pstrdup(NameStr(fdwform->fdwname));
	fdw->fdwhandler = fdwform->fdwhandler;
	fdw->fdwvalidator = fdwform->fdwvalidator;

	/* Extract the fdwoptions */
	datum = SysCacheGetAttr(FOREIGNDATAWRAPPEROID,
							tp,
							Anum_pg_foreign_data_wrapper_fdwoptions,
							&isnull);
	if (isnull)
		fdw->options = NIL;
	else
		fdw->options = untransformRelOptions(datum);

	ReleaseSysCache(tp);

	return fdw;
}