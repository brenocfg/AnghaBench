#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* use_role; int remoteVersion; int numWorkers; int /*<<< orphan*/ * sync_snapshot_id; scalar_t__ isStandby; int /*<<< orphan*/  std_strings; int /*<<< orphan*/  encoding; TYPE_2__* dopt; } ;
struct TYPE_15__ {int /*<<< orphan*/  no_synchronized_snapshots; scalar_t__ serializable_deferrable; scalar_t__ enable_row_security; } ;
struct TYPE_14__ {char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_2__ DumpOptions ;
typedef  TYPE_3__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 int /*<<< orphan*/  ExecuteSqlQueryForSingleRow (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecuteSqlStatement (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * GetConnection (TYPE_3__*) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclientEncoding (int /*<<< orphan*/ *) ; 
 char* PQparameterStatus (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQsetClientEncoding (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  extra_float_digits ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fmtId (char*) ; 
 int /*<<< orphan*/ * get_synchronized_snapshot (TYPE_3__*) ; 
 scalar_t__ have_extra_float_digits ; 
 void* pg_strdup (char const*) ; 
 scalar_t__ quote_all_identifiers ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
setup_connection(Archive *AH, const char *dumpencoding,
				 const char *dumpsnapshot, char *use_role)
{
	DumpOptions *dopt = AH->dopt;
	PGconn	   *conn = GetConnection(AH);
	const char *std_strings;

	PQclear(ExecuteSqlQueryForSingleRow(AH, ALWAYS_SECURE_SEARCH_PATH_SQL));

	/*
	 * Set the client encoding if requested.
	 */
	if (dumpencoding)
	{
		if (PQsetClientEncoding(conn, dumpencoding) < 0)
			fatal("invalid client encoding \"%s\" specified",
				  dumpencoding);
	}

	/*
	 * Get the active encoding and the standard_conforming_strings setting, so
	 * we know how to escape strings.
	 */
	AH->encoding = PQclientEncoding(conn);

	std_strings = PQparameterStatus(conn, "standard_conforming_strings");
	AH->std_strings = (std_strings && strcmp(std_strings, "on") == 0);

	/*
	 * Set the role if requested.  In a parallel dump worker, we'll be passed
	 * use_role == NULL, but AH->use_role is already set (if user specified it
	 * originally) and we should use that.
	 */
	if (!use_role && AH->use_role)
		use_role = AH->use_role;

	/* Set the role if requested */
	if (use_role && AH->remoteVersion >= 80100)
	{
		PQExpBuffer query = createPQExpBuffer();

		appendPQExpBuffer(query, "SET ROLE %s", fmtId(use_role));
		ExecuteSqlStatement(AH, query->data);
		destroyPQExpBuffer(query);

		/* save it for possible later use by parallel workers */
		if (!AH->use_role)
			AH->use_role = pg_strdup(use_role);
	}

	/* Set the datestyle to ISO to ensure the dump's portability */
	ExecuteSqlStatement(AH, "SET DATESTYLE = ISO");

	/* Likewise, avoid using sql_standard intervalstyle */
	if (AH->remoteVersion >= 80400)
		ExecuteSqlStatement(AH, "SET INTERVALSTYLE = POSTGRES");

	/*
	 * Use an explicitly specified extra_float_digits if it has been provided.
	 * Otherwise, set extra_float_digits so that we can dump float data
	 * exactly (given correctly implemented float I/O code, anyway).
	 */
	if (have_extra_float_digits)
	{
		PQExpBuffer q = createPQExpBuffer();

		appendPQExpBuffer(q, "SET extra_float_digits TO %d",
						  extra_float_digits);
		ExecuteSqlStatement(AH, q->data);
		destroyPQExpBuffer(q);
	}
	else if (AH->remoteVersion >= 90000)
		ExecuteSqlStatement(AH, "SET extra_float_digits TO 3");
	else
		ExecuteSqlStatement(AH, "SET extra_float_digits TO 2");

	/*
	 * If synchronized scanning is supported, disable it, to prevent
	 * unpredictable changes in row ordering across a dump and reload.
	 */
	if (AH->remoteVersion >= 80300)
		ExecuteSqlStatement(AH, "SET synchronize_seqscans TO off");

	/*
	 * Disable timeouts if supported.
	 */
	ExecuteSqlStatement(AH, "SET statement_timeout = 0");
	if (AH->remoteVersion >= 90300)
		ExecuteSqlStatement(AH, "SET lock_timeout = 0");
	if (AH->remoteVersion >= 90600)
		ExecuteSqlStatement(AH, "SET idle_in_transaction_session_timeout = 0");

	/*
	 * Quote all identifiers, if requested.
	 */
	if (quote_all_identifiers && AH->remoteVersion >= 90100)
		ExecuteSqlStatement(AH, "SET quote_all_identifiers = true");

	/*
	 * Adjust row-security mode, if supported.
	 */
	if (AH->remoteVersion >= 90500)
	{
		if (dopt->enable_row_security)
			ExecuteSqlStatement(AH, "SET row_security = on");
		else
			ExecuteSqlStatement(AH, "SET row_security = off");
	}

	/*
	 * Start transaction-snapshot mode transaction to dump consistent data.
	 */
	ExecuteSqlStatement(AH, "BEGIN");
	if (AH->remoteVersion >= 90100)
	{
		/*
		 * To support the combination of serializable_deferrable with the jobs
		 * option we use REPEATABLE READ for the worker connections that are
		 * passed a snapshot.  As long as the snapshot is acquired in a
		 * SERIALIZABLE, READ ONLY, DEFERRABLE transaction, its use within a
		 * REPEATABLE READ transaction provides the appropriate integrity
		 * guarantees.  This is a kluge, but safe for back-patching.
		 */
		if (dopt->serializable_deferrable && AH->sync_snapshot_id == NULL)
			ExecuteSqlStatement(AH,
								"SET TRANSACTION ISOLATION LEVEL "
								"SERIALIZABLE, READ ONLY, DEFERRABLE");
		else
			ExecuteSqlStatement(AH,
								"SET TRANSACTION ISOLATION LEVEL "
								"REPEATABLE READ, READ ONLY");
	}
	else
	{
		ExecuteSqlStatement(AH,
							"SET TRANSACTION ISOLATION LEVEL "
							"SERIALIZABLE, READ ONLY");
	}

	/*
	 * If user specified a snapshot to use, select that.  In a parallel dump
	 * worker, we'll be passed dumpsnapshot == NULL, but AH->sync_snapshot_id
	 * is already set (if the server can handle it) and we should use that.
	 */
	if (dumpsnapshot)
		AH->sync_snapshot_id = pg_strdup(dumpsnapshot);

	if (AH->sync_snapshot_id)
	{
		PQExpBuffer query = createPQExpBuffer();

		appendPQExpBufferStr(query, "SET TRANSACTION SNAPSHOT ");
		appendStringLiteralConn(query, AH->sync_snapshot_id, conn);
		ExecuteSqlStatement(AH, query->data);
		destroyPQExpBuffer(query);
	}
	else if (AH->numWorkers > 1 &&
			 AH->remoteVersion >= 90200 &&
			 !dopt->no_synchronized_snapshots)
	{
		if (AH->isStandby && AH->remoteVersion < 100000)
			fatal("Synchronized snapshots on standby servers are not supported by this server version.\n"
				  "Run with --no-synchronized-snapshots instead if you do not need\n"
				  "synchronized snapshots.");


		AH->sync_snapshot_id = get_synchronized_snapshot(AH);
	}
}