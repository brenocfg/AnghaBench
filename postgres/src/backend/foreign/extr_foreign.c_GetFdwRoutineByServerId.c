#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fdwname; int /*<<< orphan*/  fdwhandler; } ;
struct TYPE_3__ {int /*<<< orphan*/  srvfdw; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_foreign_server ;
typedef  TYPE_2__* Form_pg_foreign_data_wrapper ;
typedef  int /*<<< orphan*/  FdwRoutine ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOREIGNDATAWRAPPEROID ; 
 int /*<<< orphan*/  FOREIGNSERVEROID ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetFdwRoutine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

FdwRoutine *
GetFdwRoutineByServerId(Oid serverid)
{
	HeapTuple	tp;
	Form_pg_foreign_data_wrapper fdwform;
	Form_pg_foreign_server serverform;
	Oid			fdwid;
	Oid			fdwhandler;

	/* Get foreign-data wrapper OID for the server. */
	tp = SearchSysCache1(FOREIGNSERVEROID, ObjectIdGetDatum(serverid));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "cache lookup failed for foreign server %u", serverid);
	serverform = (Form_pg_foreign_server) GETSTRUCT(tp);
	fdwid = serverform->srvfdw;
	ReleaseSysCache(tp);

	/* Get handler function OID for the FDW. */
	tp = SearchSysCache1(FOREIGNDATAWRAPPEROID, ObjectIdGetDatum(fdwid));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "cache lookup failed for foreign-data wrapper %u", fdwid);
	fdwform = (Form_pg_foreign_data_wrapper) GETSTRUCT(tp);
	fdwhandler = fdwform->fdwhandler;

	/* Complain if FDW has been set to NO HANDLER. */
	if (!OidIsValid(fdwhandler))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("foreign-data wrapper \"%s\" has no handler",
						NameStr(fdwform->fdwname))));

	ReleaseSysCache(tp);

	/* And finally, call the handler function. */
	return GetFdwRoutine(fdwhandler);
}