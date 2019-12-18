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
struct TYPE_5__ {int /*<<< orphan*/  options; int /*<<< orphan*/ * serverversion; int /*<<< orphan*/ * servertype; int /*<<< orphan*/  fdwid; int /*<<< orphan*/  owner; int /*<<< orphan*/  servername; int /*<<< orphan*/  serverid; } ;
struct TYPE_4__ {int /*<<< orphan*/  srvfdw; int /*<<< orphan*/  srvowner; int /*<<< orphan*/  srvname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_foreign_server ;
typedef  TYPE_2__ ForeignServer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_foreign_server_srvoptions ; 
 int /*<<< orphan*/  Anum_pg_foreign_server_srvtype ; 
 int /*<<< orphan*/  Anum_pg_foreign_server_srvversion ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOREIGNSERVEROID ; 
 int FSV_MISSING_OK ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untransformRelOptions (int /*<<< orphan*/ ) ; 

ForeignServer *
GetForeignServerExtended(Oid serverid, bits16 flags)
{
	Form_pg_foreign_server serverform;
	ForeignServer *server;
	HeapTuple	tp;
	Datum		datum;
	bool		isnull;

	tp = SearchSysCache1(FOREIGNSERVEROID, ObjectIdGetDatum(serverid));

	if (!HeapTupleIsValid(tp))
	{
		if ((flags & FSV_MISSING_OK) == 0)
			elog(ERROR, "cache lookup failed for foreign server %u", serverid);
		return NULL;
	}

	serverform = (Form_pg_foreign_server) GETSTRUCT(tp);

	server = (ForeignServer *) palloc(sizeof(ForeignServer));
	server->serverid = serverid;
	server->servername = pstrdup(NameStr(serverform->srvname));
	server->owner = serverform->srvowner;
	server->fdwid = serverform->srvfdw;

	/* Extract server type */
	datum = SysCacheGetAttr(FOREIGNSERVEROID,
							tp,
							Anum_pg_foreign_server_srvtype,
							&isnull);
	server->servertype = isnull ? NULL : TextDatumGetCString(datum);

	/* Extract server version */
	datum = SysCacheGetAttr(FOREIGNSERVEROID,
							tp,
							Anum_pg_foreign_server_srvversion,
							&isnull);
	server->serverversion = isnull ? NULL : TextDatumGetCString(datum);

	/* Extract the srvoptions */
	datum = SysCacheGetAttr(FOREIGNSERVEROID,
							tp,
							Anum_pg_foreign_server_srvoptions,
							&isnull);
	if (isnull)
		server->options = NIL;
	else
		server->options = untransformRelOptions(datum);

	ReleaseSysCache(tp);

	return server;
}