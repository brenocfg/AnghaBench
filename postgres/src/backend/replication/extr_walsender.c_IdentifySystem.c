#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xloc ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  sysid ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TupOutputState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/ * CreateDestReceiver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DestRemoteSimple ; 
 int GetFlushRecPtr () ; 
 int GetStandbyFlushRecPtr () ; 
 int /*<<< orphan*/  GetSystemIdentifier () ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ MyDatabaseId ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  TupleDescInitBuiltinEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* UINT64_FORMAT ; 
 scalar_t__ am_cascading_walsender ; 
 int /*<<< orphan*/ * begin_tup_output_tupdesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_tup_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  end_tup_output (int /*<<< orphan*/ *) ; 
 char* get_database_name (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static void
IdentifySystem(void)
{
	char		sysid[32];
	char		xloc[MAXFNAMELEN];
	XLogRecPtr	logptr;
	char	   *dbname = NULL;
	DestReceiver *dest;
	TupOutputState *tstate;
	TupleDesc	tupdesc;
	Datum		values[4];
	bool		nulls[4];

	/*
	 * Reply with a result set with one row, four columns. First col is system
	 * ID, second is timeline ID, third is current xlog location and the
	 * fourth contains the database name if we are connected to one.
	 */

	snprintf(sysid, sizeof(sysid), UINT64_FORMAT,
			 GetSystemIdentifier());

	am_cascading_walsender = RecoveryInProgress();
	if (am_cascading_walsender)
	{
		/* this also updates ThisTimeLineID */
		logptr = GetStandbyFlushRecPtr();
	}
	else
		logptr = GetFlushRecPtr();

	snprintf(xloc, sizeof(xloc), "%X/%X", (uint32) (logptr >> 32), (uint32) logptr);

	if (MyDatabaseId != InvalidOid)
	{
		MemoryContext cur = CurrentMemoryContext;

		/* syscache access needs a transaction env. */
		StartTransactionCommand();
		/* make dbname live outside TX context */
		MemoryContextSwitchTo(cur);
		dbname = get_database_name(MyDatabaseId);
		CommitTransactionCommand();
		/* CommitTransactionCommand switches to TopMemoryContext */
		MemoryContextSwitchTo(cur);
	}

	dest = CreateDestReceiver(DestRemoteSimple);
	MemSet(nulls, false, sizeof(nulls));

	/* need a tuple descriptor representing four columns */
	tupdesc = CreateTemplateTupleDesc(4);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 1, "systemid",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 2, "timeline",
							  INT4OID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 3, "xlogpos",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 4, "dbname",
							  TEXTOID, -1, 0);

	/* prepare for projection of tuples */
	tstate = begin_tup_output_tupdesc(dest, tupdesc, &TTSOpsVirtual);

	/* column 1: system identifier */
	values[0] = CStringGetTextDatum(sysid);

	/* column 2: timeline */
	values[1] = Int32GetDatum(ThisTimeLineID);

	/* column 3: wal location */
	values[2] = CStringGetTextDatum(xloc);

	/* column 4: database name, or NULL if none */
	if (dbname)
		values[3] = CStringGetTextDatum(dbname);
	else
		nulls[3] = true;

	/* send it to dest */
	do_tup_output(tstate, values, nulls);

	end_tup_output(tstate);
}