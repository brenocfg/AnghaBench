#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_29__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  int teReqs ;
struct TYPE_33__ {char* desc; int reqs; char* namespace; int /*<<< orphan*/  tag; scalar_t__ created; int /*<<< orphan*/ * copyStmt; scalar_t__ hadDumper; int /*<<< orphan*/ * defn; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_34__ {scalar_t__ n_errors; TYPE_2__* ropt; } ;
struct TYPE_37__ {scalar_t__ outputKind; TYPE_29__ public; int /*<<< orphan*/  (* PrintTocDataPtr ) (TYPE_4__*,TYPE_1__*) ;int /*<<< orphan*/  connection; TYPE_1__* lastErrorTE; TYPE_1__* currentTE; } ;
struct TYPE_36__ {int /*<<< orphan*/  data; } ;
struct TYPE_35__ {int /*<<< orphan*/  dbname; scalar_t__ noDataForFailedTables; int /*<<< orphan*/  dataOnly; int /*<<< orphan*/  suppressDumpWarnings; } ;
typedef  TYPE_2__ RestoreOptions ;
typedef  TYPE_3__ PQExpBufferData ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransaction (TYPE_29__*) ; 
 int /*<<< orphan*/  EndDBCopyMode (TYPE_29__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OUTPUT_COPYDATA ; 
 void* OUTPUT_OTHERDATA ; 
 void* OUTPUT_SQLCMDS ; 
 int PQserverVersion (int /*<<< orphan*/ ) ; 
 int REQ_DATA ; 
 int REQ_SCHEMA ; 
 scalar_t__ RestoringToDB (TYPE_4__*) ; 
 int /*<<< orphan*/  StartTransaction (TYPE_29__*) ; 
 int WORKER_CREATE_DONE ; 
 int WORKER_IGNORED_ERRORS ; 
 int WORKER_INHIBIT_DATA ; 
 int WORKER_OK ; 
 int /*<<< orphan*/  _becomeOwner (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _disableTriggersIfNecessary (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _enableTriggersIfNecessary (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  _printTocEntry (TYPE_4__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  _reconnectToDB (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _selectOutputSchema (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_4__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  fmtQualifiedId (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inhibit_data_for_failed_table (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  mark_create_done (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_info (char*,char*,...) ; 
 int /*<<< orphan*/  pg_log_warning (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_1__*) ; 

__attribute__((used)) static int
restore_toc_entry(ArchiveHandle *AH, TocEntry *te, bool is_parallel)
{
	RestoreOptions *ropt = AH->public.ropt;
	int			status = WORKER_OK;
	teReqs		reqs;
	bool		defnDumped;

	AH->currentTE = te;

	/* Dump any relevant dump warnings to stderr */
	if (!ropt->suppressDumpWarnings && strcmp(te->desc, "WARNING") == 0)
	{
		if (!ropt->dataOnly && te->defn != NULL && strlen(te->defn) != 0)
			pg_log_warning("warning from original dump file: %s", te->defn);
		else if (te->copyStmt != NULL && strlen(te->copyStmt) != 0)
			pg_log_warning("warning from original dump file: %s", te->copyStmt);
	}

	/* Work out what, if anything, we want from this entry */
	reqs = te->reqs;

	defnDumped = false;

	/*
	 * If it has a schema component that we want, then process that
	 */
	if ((reqs & REQ_SCHEMA) != 0)
	{
		/* Show namespace in log message if available */
		if (te->namespace)
			pg_log_info("creating %s \"%s.%s\"",
						te->desc, te->namespace, te->tag);
		else
			pg_log_info("creating %s \"%s\"",
						te->desc, te->tag);

		_printTocEntry(AH, te, false);
		defnDumped = true;

		if (strcmp(te->desc, "TABLE") == 0)
		{
			if (AH->lastErrorTE == te)
			{
				/*
				 * We failed to create the table. If
				 * --no-data-for-failed-tables was given, mark the
				 * corresponding TABLE DATA to be ignored.
				 *
				 * In the parallel case this must be done in the parent, so we
				 * just set the return value.
				 */
				if (ropt->noDataForFailedTables)
				{
					if (is_parallel)
						status = WORKER_INHIBIT_DATA;
					else
						inhibit_data_for_failed_table(AH, te);
				}
			}
			else
			{
				/*
				 * We created the table successfully.  Mark the corresponding
				 * TABLE DATA for possible truncation.
				 *
				 * In the parallel case this must be done in the parent, so we
				 * just set the return value.
				 */
				if (is_parallel)
					status = WORKER_CREATE_DONE;
				else
					mark_create_done(AH, te);
			}
		}

		/*
		 * If we created a DB, connect to it.  Also, if we changed DB
		 * properties, reconnect to ensure that relevant GUC settings are
		 * applied to our session.
		 */
		if (strcmp(te->desc, "DATABASE") == 0 ||
			strcmp(te->desc, "DATABASE PROPERTIES") == 0)
		{
			PQExpBufferData connstr;

			initPQExpBuffer(&connstr);
			appendPQExpBufferStr(&connstr, "dbname=");
			appendConnStrVal(&connstr, te->tag);
			/* Abandon struct, but keep its buffer until process exit. */

			pg_log_info("connecting to new database \"%s\"", te->tag);
			_reconnectToDB(AH, te->tag);
			ropt->dbname = connstr.data;
		}
	}

	/*
	 * If it has a data component that we want, then process that
	 */
	if ((reqs & REQ_DATA) != 0)
	{
		/*
		 * hadDumper will be set if there is genuine data component for this
		 * node. Otherwise, we need to check the defn field for statements
		 * that need to be executed in data-only restores.
		 */
		if (te->hadDumper)
		{
			/*
			 * If we can output the data, then restore it.
			 */
			if (AH->PrintTocDataPtr != NULL)
			{
				_printTocEntry(AH, te, true);

				if (strcmp(te->desc, "BLOBS") == 0 ||
					strcmp(te->desc, "BLOB COMMENTS") == 0)
				{
					pg_log_info("processing %s", te->desc);

					_selectOutputSchema(AH, "pg_catalog");

					/* Send BLOB COMMENTS data to ExecuteSimpleCommands() */
					if (strcmp(te->desc, "BLOB COMMENTS") == 0)
						AH->outputKind = OUTPUT_OTHERDATA;

					AH->PrintTocDataPtr(AH, te);

					AH->outputKind = OUTPUT_SQLCMDS;
				}
				else
				{
					_disableTriggersIfNecessary(AH, te);

					/* Select owner and schema as necessary */
					_becomeOwner(AH, te);
					_selectOutputSchema(AH, te->namespace);

					pg_log_info("processing data for table \"%s.%s\"",
								te->namespace, te->tag);

					/*
					 * In parallel restore, if we created the table earlier in
					 * the run then we wrap the COPY in a transaction and
					 * precede it with a TRUNCATE.  If archiving is not on
					 * this prevents WAL-logging the COPY.  This obtains a
					 * speedup similar to that from using single_txn mode in
					 * non-parallel restores.
					 */
					if (is_parallel && te->created)
					{
						/*
						 * Parallel restore is always talking directly to a
						 * server, so no need to see if we should issue BEGIN.
						 */
						StartTransaction(&AH->public);

						/*
						 * If the server version is >= 8.4, make sure we issue
						 * TRUNCATE with ONLY so that child tables are not
						 * wiped.
						 */
						ahprintf(AH, "TRUNCATE TABLE %s%s;\n\n",
								 (PQserverVersion(AH->connection) >= 80400 ?
								  "ONLY " : ""),
								 fmtQualifiedId(te->namespace, te->tag));
					}

					/*
					 * If we have a copy statement, use it.
					 */
					if (te->copyStmt && strlen(te->copyStmt) > 0)
					{
						ahprintf(AH, "%s", te->copyStmt);
						AH->outputKind = OUTPUT_COPYDATA;
					}
					else
						AH->outputKind = OUTPUT_OTHERDATA;

					AH->PrintTocDataPtr(AH, te);

					/*
					 * Terminate COPY if needed.
					 */
					if (AH->outputKind == OUTPUT_COPYDATA &&
						RestoringToDB(AH))
						EndDBCopyMode(&AH->public, te->tag);
					AH->outputKind = OUTPUT_SQLCMDS;

					/* close out the transaction started above */
					if (is_parallel && te->created)
						CommitTransaction(&AH->public);

					_enableTriggersIfNecessary(AH, te);
				}
			}
		}
		else if (!defnDumped)
		{
			/* If we haven't already dumped the defn part, do so now */
			pg_log_info("executing %s %s", te->desc, te->tag);
			_printTocEntry(AH, te, false);
		}
	}

	if (AH->public.n_errors > 0 && status == WORKER_OK)
		status = WORKER_IGNORED_ERRORS;

	return status;
}