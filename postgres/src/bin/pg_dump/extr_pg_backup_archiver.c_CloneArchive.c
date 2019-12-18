#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* ropt; scalar_t__ n_errors; } ;
struct TYPE_18__ {scalar_t__ mode; int /*<<< orphan*/ * connection; int /*<<< orphan*/  (* ClonePtr ) (TYPE_4__*) ;TYPE_1__ public; scalar_t__ savedPassword; int /*<<< orphan*/ * currTablespace; int /*<<< orphan*/ * currSchema; int /*<<< orphan*/ * currUser; int /*<<< orphan*/ * connCancel; int /*<<< orphan*/  sqlparse; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {char* pghost; char* pgport; char* username; int /*<<< orphan*/  promptPassword; int /*<<< orphan*/  dbname; } ;
typedef  TYPE_2__ RestoreOptions ;
typedef  TYPE_3__ PQExpBufferData ;
typedef  TYPE_4__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConnectDatabase (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQdb (int /*<<< orphan*/ *) ; 
 char* PQhost (int /*<<< orphan*/ *) ; 
 char* PQport (int /*<<< orphan*/ *) ; 
 char* PQuser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRI_NO ; 
 int /*<<< orphan*/  _doSetFixedOutputState (TYPE_4__*) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 scalar_t__ archModeRead ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_strdup (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_3__*) ; 

ArchiveHandle *
CloneArchive(ArchiveHandle *AH)
{
	ArchiveHandle *clone;

	/* Make a "flat" copy */
	clone = (ArchiveHandle *) pg_malloc(sizeof(ArchiveHandle));
	memcpy(clone, AH, sizeof(ArchiveHandle));

	/* Handle format-independent fields */
	memset(&(clone->sqlparse), 0, sizeof(clone->sqlparse));

	/* The clone will have its own connection, so disregard connection state */
	clone->connection = NULL;
	clone->connCancel = NULL;
	clone->currUser = NULL;
	clone->currSchema = NULL;
	clone->currTablespace = NULL;

	/* savedPassword must be local in case we change it while connecting */
	if (clone->savedPassword)
		clone->savedPassword = pg_strdup(clone->savedPassword);

	/* clone has its own error count, too */
	clone->public.n_errors = 0;

	/*
	 * Connect our new clone object to the database: In parallel restore the
	 * parent is already disconnected, because we can connect the worker
	 * processes independently to the database (no snapshot sync required). In
	 * parallel backup we clone the parent's existing connection.
	 */
	if (AH->mode == archModeRead)
	{
		RestoreOptions *ropt = AH->public.ropt;

		Assert(AH->connection == NULL);

		/* this also sets clone->connection */
		ConnectDatabase((Archive *) clone, ropt->dbname,
						ropt->pghost, ropt->pgport, ropt->username,
						ropt->promptPassword);

		/* re-establish fixed state */
		_doSetFixedOutputState(clone);
	}
	else
	{
		PQExpBufferData connstr;
		char	   *pghost;
		char	   *pgport;
		char	   *username;

		Assert(AH->connection != NULL);

		/*
		 * Even though we are technically accessing the parent's database
		 * object here, these functions are fine to be called like that
		 * because all just return a pointer and do not actually send/receive
		 * any data to/from the database.
		 */
		initPQExpBuffer(&connstr);
		appendPQExpBufferStr(&connstr, "dbname=");
		appendConnStrVal(&connstr, PQdb(AH->connection));
		pghost = PQhost(AH->connection);
		pgport = PQport(AH->connection);
		username = PQuser(AH->connection);

		/* this also sets clone->connection */
		ConnectDatabase((Archive *) clone, connstr.data,
						pghost, pgport, username, TRI_NO);

		termPQExpBuffer(&connstr);
		/* setupDumpWorker will fix up connection state */
	}

	/* Let the format-specific code have a chance too */
	clone->ClonePtr(clone);

	Assert(clone->connection != NULL);
	return clone;
}