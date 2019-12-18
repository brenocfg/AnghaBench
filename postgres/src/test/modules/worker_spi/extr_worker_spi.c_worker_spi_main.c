#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* name; void* schema; } ;
typedef  TYPE_1__ worktable ;
typedef  void* int32 ;
struct TYPE_12__ {int /*<<< orphan*/  bgw_name; } ;
struct TYPE_11__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
struct TYPE_10__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BackgroundWorkerInitializeConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackgroundWorkerUnblockSignals () ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 void* DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_8__* MyBgworkerEntry ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  PG_WAIT_EXTENSION ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int SPI_OK_UPDATE_RETURNING ; 
 int /*<<< orphan*/  SPI_connect () ; 
 int SPI_execute (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_finish () ; 
 int /*<<< orphan*/  SPI_getbinval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ SPI_processed ; 
 TYPE_7__* SPI_tuptable ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  SetCurrentStatementStartTimestamp () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,void*,void*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int,...) ; 
 int got_sighup ; 
 int /*<<< orphan*/  got_sigterm ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  initialize_worker_spi (TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgstat_report_stat (int) ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 void* pstrdup (char*) ; 
 void* quote_identifier (void*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  worker_spi_database ; 
 long worker_spi_naptime ; 
 int /*<<< orphan*/  worker_spi_sighup ; 
 int /*<<< orphan*/  worker_spi_sigterm ; 

void
worker_spi_main(Datum main_arg)
{
	int			index = DatumGetInt32(main_arg);
	worktable  *table;
	StringInfoData buf;
	char		name[20];

	table = palloc(sizeof(worktable));
	sprintf(name, "schema%d", index);
	table->schema = pstrdup(name);
	table->name = pstrdup("counted");

	/* Establish signal handlers before unblocking signals. */
	pqsignal(SIGHUP, worker_spi_sighup);
	pqsignal(SIGTERM, worker_spi_sigterm);

	/* We're now ready to receive signals */
	BackgroundWorkerUnblockSignals();

	/* Connect to our database */
	BackgroundWorkerInitializeConnection(worker_spi_database, NULL, 0);

	elog(LOG, "%s initialized with %s.%s",
		 MyBgworkerEntry->bgw_name, table->schema, table->name);
	initialize_worker_spi(table);

	/*
	 * Quote identifiers passed to us.  Note that this must be done after
	 * initialize_worker_spi, because that routine assumes the names are not
	 * quoted.
	 *
	 * Note some memory might be leaked here.
	 */
	table->schema = quote_identifier(table->schema);
	table->name = quote_identifier(table->name);

	initStringInfo(&buf);
	appendStringInfo(&buf,
					 "WITH deleted AS (DELETE "
					 "FROM %s.%s "
					 "WHERE type = 'delta' RETURNING value), "
					 "total AS (SELECT coalesce(sum(value), 0) as sum "
					 "FROM deleted) "
					 "UPDATE %s.%s "
					 "SET value = %s.value + total.sum "
					 "FROM total WHERE type = 'total' "
					 "RETURNING %s.value",
					 table->schema, table->name,
					 table->schema, table->name,
					 table->name,
					 table->name);

	/*
	 * Main loop: do this until the SIGTERM handler tells us to terminate
	 */
	while (!got_sigterm)
	{
		int			ret;

		/*
		 * Background workers mustn't call usleep() or any direct equivalent:
		 * instead, they may wait on their process latch, which sleeps as
		 * necessary, but is awakened if postmaster dies.  That way the
		 * background process goes away immediately in an emergency.
		 */
		(void) WaitLatch(MyLatch,
						 WL_LATCH_SET | WL_TIMEOUT | WL_EXIT_ON_PM_DEATH,
						 worker_spi_naptime * 1000L,
						 PG_WAIT_EXTENSION);
		ResetLatch(MyLatch);

		CHECK_FOR_INTERRUPTS();

		/*
		 * In case of a SIGHUP, just reload the configuration.
		 */
		if (got_sighup)
		{
			got_sighup = false;
			ProcessConfigFile(PGC_SIGHUP);
		}

		/*
		 * Start a transaction on which we can run queries.  Note that each
		 * StartTransactionCommand() call should be preceded by a
		 * SetCurrentStatementStartTimestamp() call, which sets both the time
		 * for the statement we're about the run, and also the transaction
		 * start time.  Also, each other query sent to SPI should probably be
		 * preceded by SetCurrentStatementStartTimestamp(), so that statement
		 * start time is always up to date.
		 *
		 * The SPI_connect() call lets us run queries through the SPI manager,
		 * and the PushActiveSnapshot() call creates an "active" snapshot
		 * which is necessary for queries to have MVCC data to work on.
		 *
		 * The pgstat_report_activity() call makes our activity visible
		 * through the pgstat views.
		 */
		SetCurrentStatementStartTimestamp();
		StartTransactionCommand();
		SPI_connect();
		PushActiveSnapshot(GetTransactionSnapshot());
		pgstat_report_activity(STATE_RUNNING, buf.data);

		/* We can now execute queries via SPI */
		ret = SPI_execute(buf.data, false, 0);

		if (ret != SPI_OK_UPDATE_RETURNING)
			elog(FATAL, "cannot select from table %s.%s: error code %d",
				 table->schema, table->name, ret);

		if (SPI_processed > 0)
		{
			bool		isnull;
			int32		val;

			val = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
											  SPI_tuptable->tupdesc,
											  1, &isnull));
			if (!isnull)
				elog(LOG, "%s: count in %s.%s is now %d",
					 MyBgworkerEntry->bgw_name,
					 table->schema, table->name, val);
		}

		/*
		 * And finish our transaction.
		 */
		SPI_finish();
		PopActiveSnapshot();
		CommitTransactionCommand();
		pgstat_report_stat(false);
		pgstat_report_activity(STATE_IDLE, NULL);
	}

	proc_exit(1);
}