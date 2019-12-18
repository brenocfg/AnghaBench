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
typedef  int /*<<< orphan*/  sigjmp_buf ;
struct TYPE_4__ {int /*<<< orphan*/  procLatch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * walwriterLatch; } ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AbortBufferIO () ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOXact_Buffers (int) ; 
 int /*<<< orphan*/  AtEOXact_Files (int) ; 
 int /*<<< orphan*/  AtEOXact_HashTables (int) ; 
 int /*<<< orphan*/  AtEOXact_SMgr () ; 
 int /*<<< orphan*/  BlockSig ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  EmitErrorReport () ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 long HIBERNATE_FACTOR ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 int LOOPS_UNTIL_HIBERNATE ; 
 int /*<<< orphan*/  LWLockReleaseAll () ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyLatch ; 
 TYPE_2__* MyProc ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PG_exception_stack ; 
 TYPE_1__* ProcGlobal ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  ReleaseAuxProcessResources (int) ; 
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
 int /*<<< orphan*/  SetWalWriterSleeping (int) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  UnlockBuffers () ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_WRITER_MAIN ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalShutdownHandler ; 
 int /*<<< orphan*/  WalSigHupHandler ; 
 long WalWriterDelay ; 
 scalar_t__ XLogBackgroundFlush () ; 
 int /*<<< orphan*/ * error_context_stack ; 
 int got_SIGHUP ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown_requested ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smgrcloseall () ; 
 int /*<<< orphan*/  wal_quickdie ; 
 int /*<<< orphan*/  walwriter_sigusr1_handler ; 

void
WalWriterMain(void)
{
	sigjmp_buf	local_sigjmp_buf;
	MemoryContext walwriter_context;
	int			left_till_hibernate;
	bool		hibernating;

	/*
	 * Properly accept or ignore signals the postmaster might send us
	 *
	 * We have no particular use for SIGINT at the moment, but seems
	 * reasonable to treat like SIGTERM.
	 */
	pqsignal(SIGHUP, WalSigHupHandler); /* set flag to read config file */
	pqsignal(SIGINT, WalShutdownHandler);	/* request shutdown */
	pqsignal(SIGTERM, WalShutdownHandler);	/* request shutdown */
	pqsignal(SIGQUIT, wal_quickdie);	/* hard crash time */
	pqsignal(SIGALRM, SIG_IGN);
	pqsignal(SIGPIPE, SIG_IGN);
	pqsignal(SIGUSR1, walwriter_sigusr1_handler);
	pqsignal(SIGUSR2, SIG_IGN); /* not used */

	/*
	 * Reset some signals that are accepted by postmaster but not here
	 */
	pqsignal(SIGCHLD, SIG_DFL);

	/* We allow SIGQUIT (quickdie) at all times */
	sigdelset(&BlockSig, SIGQUIT);

	/*
	 * Create a memory context that we will do all our work in.  We do this so
	 * that we can reset the context during error recovery and thereby avoid
	 * possible memory leaks.  Formerly this code just ran in
	 * TopMemoryContext, but resetting that would be a really bad idea.
	 */
	walwriter_context = AllocSetContextCreate(TopMemoryContext,
											  "Wal Writer",
											  ALLOCSET_DEFAULT_SIZES);
	MemoryContextSwitchTo(walwriter_context);

	/*
	 * If an exception is encountered, processing resumes here.
	 *
	 * This code is heavily based on bgwriter.c, q.v.
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
		 * about in walwriter, but we do have LWLocks, and perhaps buffers?
		 */
		LWLockReleaseAll();
		ConditionVariableCancelSleep();
		pgstat_report_wait_end();
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
		MemoryContextSwitchTo(walwriter_context);
		FlushErrorState();

		/* Flush any leaked data in the top-level context */
		MemoryContextResetAndDeleteChildren(walwriter_context);

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
	left_till_hibernate = LOOPS_UNTIL_HIBERNATE;
	hibernating = false;
	SetWalWriterSleeping(false);

	/*
	 * Advertise our latch that backends can use to wake us up while we're
	 * sleeping.
	 */
	ProcGlobal->walwriterLatch = &MyProc->procLatch;

	/*
	 * Loop forever
	 */
	for (;;)
	{
		long		cur_timeout;

		/*
		 * Advertise whether we might hibernate in this cycle.  We do this
		 * before resetting the latch to ensure that any async commits will
		 * see the flag set if they might possibly need to wake us up, and
		 * that we won't miss any signal they send us.  (If we discover work
		 * to do in the last cycle before we would hibernate, the global flag
		 * will be set unnecessarily, but little harm is done.)  But avoid
		 * touching the global flag if it doesn't need to change.
		 */
		if (hibernating != (left_till_hibernate <= 1))
		{
			hibernating = (left_till_hibernate <= 1);
			SetWalWriterSleeping(hibernating);
		}

		/* Clear any already-pending wakeups */
		ResetLatch(MyLatch);

		/*
		 * Process any requests or signals received recently.
		 */
		if (got_SIGHUP)
		{
			got_SIGHUP = false;
			ProcessConfigFile(PGC_SIGHUP);
		}
		if (shutdown_requested)
		{
			/* Normal exit from the walwriter is here */
			proc_exit(0);		/* done */
		}

		/*
		 * Do what we're here for; then, if XLogBackgroundFlush() found useful
		 * work to do, reset hibernation counter.
		 */
		if (XLogBackgroundFlush())
			left_till_hibernate = LOOPS_UNTIL_HIBERNATE;
		else if (left_till_hibernate > 0)
			left_till_hibernate--;

		/*
		 * Sleep until we are signaled or WalWriterDelay has elapsed.  If we
		 * haven't done anything useful for quite some time, lengthen the
		 * sleep time so as to reduce the server's idle power consumption.
		 */
		if (left_till_hibernate > 0)
			cur_timeout = WalWriterDelay;	/* in ms */
		else
			cur_timeout = WalWriterDelay * HIBERNATE_FACTOR;

		(void) WaitLatch(MyLatch,
						 WL_LATCH_SET | WL_TIMEOUT | WL_EXIT_ON_PM_DEATH,
						 cur_timeout,
						 WAIT_EVENT_WAL_WRITER_MAIN);
	}
}