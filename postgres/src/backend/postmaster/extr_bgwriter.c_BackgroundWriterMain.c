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
typedef  int /*<<< orphan*/  sigjmp_buf ;
typedef  int /*<<< orphan*/  WritebackContext ;
typedef  scalar_t__ TimestampTz ;
struct TYPE_2__ {int pgprocno; } ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AbortBufferIO () ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOXact_Buffers (int) ; 
 int /*<<< orphan*/  AtEOXact_Files (int) ; 
 int /*<<< orphan*/  AtEOXact_HashTables (int) ; 
 int /*<<< orphan*/  AtEOXact_SMgr () ; 
 int BgBufferSync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BgSigHupHandler ; 
 int BgWriterDelay ; 
 int /*<<< orphan*/  BlockSig ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  EmitErrorReport () ; 
 int ExitOnAnyError ; 
 scalar_t__ FirstCallSinceLastCheckpoint () ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 void* GetCurrentTimestamp () ; 
 scalar_t__ GetLastImportantRecPtr () ; 
 int HIBERNATE_FACTOR ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 int /*<<< orphan*/  LOG_SNAPSHOT_INTERVAL_MS ; 
 int /*<<< orphan*/  LWLockReleaseAll () ; 
 scalar_t__ LogStandbySnapshot () ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyLatch ; 
 TYPE_1__* MyProc ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PG_exception_stack ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  ReleaseAuxProcessResources (int) ; 
 int /*<<< orphan*/  ReqShutdownHandler ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  StrategyNotifyBgWriter (int) ; 
 scalar_t__ TimestampTzPlusMilliseconds (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  UnlockBuffers () ; 
 int /*<<< orphan*/  WAIT_EVENT_BGWRITER_HIBERNATE ; 
 int /*<<< orphan*/  WAIT_EVENT_BGWRITER_MAIN ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int WaitLatch (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WritebackContextInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogStandbyInfoActive () ; 
 int /*<<< orphan*/  bg_quickdie ; 
 int /*<<< orphan*/  bgwriter_flush_after ; 
 int /*<<< orphan*/  bgwriter_sigusr1_handler ; 
 int /*<<< orphan*/ * error_context_stack ; 
 int got_SIGHUP ; 
 scalar_t__ last_snapshot_lsn ; 
 void* last_snapshot_ts ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_send_bgwriter () ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown_requested ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smgrcloseall () ; 

void
BackgroundWriterMain(void)
{
	sigjmp_buf	local_sigjmp_buf;
	MemoryContext bgwriter_context;
	bool		prev_hibernate;
	WritebackContext wb_context;

	/*
	 * Properly accept or ignore signals the postmaster might send us.
	 *
	 * bgwriter doesn't participate in ProcSignal signalling, but a SIGUSR1
	 * handler is still needed for latch wakeups.
	 */
	pqsignal(SIGHUP, BgSigHupHandler);	/* set flag to read config file */
	pqsignal(SIGINT, SIG_IGN);
	pqsignal(SIGTERM, ReqShutdownHandler);	/* shutdown */
	pqsignal(SIGQUIT, bg_quickdie); /* hard crash time */
	pqsignal(SIGALRM, SIG_IGN);
	pqsignal(SIGPIPE, SIG_IGN);
	pqsignal(SIGUSR1, bgwriter_sigusr1_handler);
	pqsignal(SIGUSR2, SIG_IGN);

	/*
	 * Reset some signals that are accepted by postmaster but not here
	 */
	pqsignal(SIGCHLD, SIG_DFL);

	/* We allow SIGQUIT (quickdie) at all times */
	sigdelset(&BlockSig, SIGQUIT);

	/*
	 * We just started, assume there has been either a shutdown or
	 * end-of-recovery snapshot.
	 */
	last_snapshot_ts = GetCurrentTimestamp();

	/*
	 * Create a memory context that we will do all our work in.  We do this so
	 * that we can reset the context during error recovery and thereby avoid
	 * possible memory leaks.  Formerly this code just ran in
	 * TopMemoryContext, but resetting that would be a really bad idea.
	 */
	bgwriter_context = AllocSetContextCreate(TopMemoryContext,
											 "Background Writer",
											 ALLOCSET_DEFAULT_SIZES);
	MemoryContextSwitchTo(bgwriter_context);

	WritebackContextInit(&wb_context, &bgwriter_flush_after);

	/*
	 * If an exception is encountered, processing resumes here.
	 *
	 * See notes in postgres.c about the design of this coding.
	 */
	if (sigsetjmp(local_sigjmp_buf, 1) != 0)
	{
		/* Since not using PG_TRY, must reset error stack by hand */
		error_context_stack = NULL;

		/* Prevent interrupts while cleaning up */
		HOLD_INTERRUPTS();

		/* Report the error to the server log */
		EmitErrorReport();

		/*
		 * These operations are really just a minimal subset of
		 * AbortTransaction().  We don't have very many resources to worry
		 * about in bgwriter, but we do have LWLocks, buffers, and temp files.
		 */
		LWLockReleaseAll();
		ConditionVariableCancelSleep();
		AbortBufferIO();
		UnlockBuffers();
		ReleaseAuxProcessResources(false);
		AtEOXact_Buffers(false);
		AtEOXact_SMgr();
		AtEOXact_Files(false);
		AtEOXact_HashTables(false);

		/*
		 * Now return to normal top-level context and clear ErrorContext for
		 * next time.
		 */
		MemoryContextSwitchTo(bgwriter_context);
		FlushErrorState();

		/* Flush any leaked data in the top-level context */
		MemoryContextResetAndDeleteChildren(bgwriter_context);

		/* re-initialize to avoid repeated errors causing problems */
		WritebackContextInit(&wb_context, &bgwriter_flush_after);

		/* Now we can allow interrupts again */
		RESUME_INTERRUPTS();

		/*
		 * Sleep at least 1 second after any error.  A write error is likely
		 * to be repeated, and we don't want to be filling the error logs as
		 * fast as we can.
		 */
		pg_usleep(1000000L);

		/*
		 * Close all open files after any error.  This is helpful on Windows,
		 * where holding deleted files open causes various strange errors.
		 * It's not clear we need it elsewhere, but shouldn't hurt.
		 */
		smgrcloseall();

		/* Report wait end here, when there is no further possibility of wait */
		pgstat_report_wait_end();
	}

	/* We can now handle ereport(ERROR) */
	PG_exception_stack = &local_sigjmp_buf;

	/*
	 * Unblock signals (they were blocked when the postmaster forked us)
	 */
	PG_SETMASK(&UnBlockSig);

	/*
	 * Reset hibernation state after any error.
	 */
	prev_hibernate = false;

	/*
	 * Loop forever
	 */
	for (;;)
	{
		bool		can_hibernate;
		int			rc;

		/* Clear any already-pending wakeups */
		ResetLatch(MyLatch);

		if (got_SIGHUP)
		{
			got_SIGHUP = false;
			ProcessConfigFile(PGC_SIGHUP);
		}
		if (shutdown_requested)
		{
			/*
			 * From here on, elog(ERROR) should end with exit(1), not send
			 * control back to the sigsetjmp block above
			 */
			ExitOnAnyError = true;
			/* Normal exit from the bgwriter is here */
			proc_exit(0);		/* done */
		}

		/*
		 * Do one cycle of dirty-buffer writing.
		 */
		can_hibernate = BgBufferSync(&wb_context);

		/*
		 * Send off activity statistics to the stats collector
		 */
		pgstat_send_bgwriter();

		if (FirstCallSinceLastCheckpoint())
		{
			/*
			 * After any checkpoint, close all smgr files.  This is so we
			 * won't hang onto smgr references to deleted files indefinitely.
			 */
			smgrcloseall();
		}

		/*
		 * Log a new xl_running_xacts every now and then so replication can
		 * get into a consistent state faster (think of suboverflowed
		 * snapshots) and clean up resources (locks, KnownXids*) more
		 * frequently. The costs of this are relatively low, so doing it 4
		 * times (LOG_SNAPSHOT_INTERVAL_MS) a minute seems fine.
		 *
		 * We assume the interval for writing xl_running_xacts is
		 * significantly bigger than BgWriterDelay, so we don't complicate the
		 * overall timeout handling but just assume we're going to get called
		 * often enough even if hibernation mode is active. It's not that
		 * important that LOG_SNAPSHOT_INTERVAL_MS is met strictly. To make
		 * sure we're not waking the disk up unnecessarily on an idle system
		 * we check whether there has been any WAL inserted since the last
		 * time we've logged a running xacts.
		 *
		 * We do this logging in the bgwriter as it is the only process that
		 * is run regularly and returns to its mainloop all the time. E.g.
		 * Checkpointer, when active, is barely ever in its mainloop and thus
		 * makes it hard to log regularly.
		 */
		if (XLogStandbyInfoActive() && !RecoveryInProgress())
		{
			TimestampTz timeout = 0;
			TimestampTz now = GetCurrentTimestamp();

			timeout = TimestampTzPlusMilliseconds(last_snapshot_ts,
												  LOG_SNAPSHOT_INTERVAL_MS);

			/*
			 * Only log if enough time has passed and interesting records have
			 * been inserted since the last snapshot.  Have to compare with <=
			 * instead of < because GetLastImportantRecPtr() points at the
			 * start of a record, whereas last_snapshot_lsn points just past
			 * the end of the record.
			 */
			if (now >= timeout &&
				last_snapshot_lsn <= GetLastImportantRecPtr())
			{
				last_snapshot_lsn = LogStandbySnapshot();
				last_snapshot_ts = now;
			}
		}

		/*
		 * Sleep until we are signaled or BgWriterDelay has elapsed.
		 *
		 * Note: the feedback control loop in BgBufferSync() expects that we
		 * will call it every BgWriterDelay msec.  While it's not critical for
		 * correctness that that be exact, the feedback loop might misbehave
		 * if we stray too far from that.  Hence, avoid loading this process
		 * down with latch events that are likely to happen frequently during
		 * normal operation.
		 */
		rc = WaitLatch(MyLatch,
					   WL_LATCH_SET | WL_TIMEOUT | WL_EXIT_ON_PM_DEATH,
					   BgWriterDelay /* ms */ , WAIT_EVENT_BGWRITER_MAIN);

		/*
		 * If no latch event and BgBufferSync says nothing's happening, extend
		 * the sleep in "hibernation" mode, where we sleep for much longer
		 * than bgwriter_delay says.  Fewer wakeups save electricity.  When a
		 * backend starts using buffers again, it will wake us up by setting
		 * our latch.  Because the extra sleep will persist only as long as no
		 * buffer allocations happen, this should not distort the behavior of
		 * BgBufferSync's control loop too badly; essentially, it will think
		 * that the system-wide idle interval didn't exist.
		 *
		 * There is a race condition here, in that a backend might allocate a
		 * buffer between the time BgBufferSync saw the alloc count as zero
		 * and the time we call StrategyNotifyBgWriter.  While it's not
		 * critical that we not hibernate anyway, we try to reduce the odds of
		 * that by only hibernating when BgBufferSync says nothing's happening
		 * for two consecutive cycles.  Also, we mitigate any possible
		 * consequences of a missed wakeup by not hibernating forever.
		 */
		if (rc == WL_TIMEOUT && can_hibernate && prev_hibernate)
		{
			/* Ask for notification at next buffer allocation */
			StrategyNotifyBgWriter(MyProc->pgprocno);
			/* Sleep ... */
			(void) WaitLatch(MyLatch,
							 WL_LATCH_SET | WL_TIMEOUT | WL_EXIT_ON_PM_DEATH,
							 BgWriterDelay * HIBERNATE_FACTOR,
							 WAIT_EVENT_BGWRITER_HIBERNATE);
			/* Reset the notification request in case we timed out */
			StrategyNotifyBgWriter(-1);
		}

		prev_hibernate = can_hibernate;
	}
}