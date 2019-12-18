#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_5__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 scalar_t__ AbortStartTime ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ AutoVacPID ; 
 scalar_t__ AutoVacuumingActive () ; 
 int /*<<< orphan*/  BackendStartup (TYPE_1__*) ; 
 scalar_t__ BgWriterPID ; 
 int /*<<< orphan*/  BlockSig ; 
 scalar_t__ CheckpointerPID ; 
 TYPE_1__* ConnCreate (scalar_t__) ; 
 int /*<<< orphan*/  ConnFree (TYPE_1__*) ; 
 int /*<<< orphan*/  DetermineSleepTime (struct timeval*) ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FatalError ; 
 scalar_t__ HaveCrashedWorker ; 
 scalar_t__ ImmediateShutdown ; 
 int /*<<< orphan*/  IsBinaryUpgrade ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__* ListenSocket ; 
 scalar_t__ Logging_collector ; 
 int MAXLISTEN ; 
 int /*<<< orphan*/  MaybeStartWalReceiver () ; 
 scalar_t__ MyProcPid ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 scalar_t__ PM_HOT_STANDBY ; 
 scalar_t__ PM_RECOVERY ; 
 scalar_t__ PM_RUN ; 
 scalar_t__ PM_WAIT_DEAD_END ; 
 scalar_t__ PgArchPID ; 
 scalar_t__ PgArchStartupAllowed () ; 
 scalar_t__ PgStatPID ; 
 int /*<<< orphan*/  RecheckDataDirLockFile () ; 
 int SECS_PER_MINUTE ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ SIGKILL_CHILDREN_AFTER_SECS ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int STATUS_ERROR ; 
 int /*<<< orphan*/  SendStop ; 
 scalar_t__ Shutdown ; 
 scalar_t__ StartAutoVacLauncher () ; 
 scalar_t__ StartBackgroundWriter () ; 
 scalar_t__ StartCheckpointer () ; 
 scalar_t__ StartWalWriter () ; 
 scalar_t__ StartWorkerNeeded ; 
 int /*<<< orphan*/  StreamClose (int /*<<< orphan*/ ) ; 
 scalar_t__ SysLoggerPID ; 
 scalar_t__ SysLogger_Start () ; 
 int /*<<< orphan*/  TerminateChildren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TouchSocketFiles () ; 
 int /*<<< orphan*/  TouchSocketLockFiles () ; 
 int /*<<< orphan*/  UnBlockSig ; 
 scalar_t__ WalReceiverRequested ; 
 scalar_t__ WalWriterPID ; 
 int avlauncher_needs_signal ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_socket_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ errno ; 
 int initMasks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_start_bgworkers () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 scalar_t__ pgarch_start () ; 
 scalar_t__ pgstat_start () ; 
 scalar_t__ pmState ; 
 scalar_t__ pthread_is_threaded_np () ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int start_autovac_launcher ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ServerLoop(void)
{
	fd_set		readmask;
	int			nSockets;
	time_t		last_lockfile_recheck_time,
				last_touch_time;

	last_lockfile_recheck_time = last_touch_time = time(NULL);

	nSockets = initMasks(&readmask);

	for (;;)
	{
		fd_set		rmask;
		int			selres;
		time_t		now;

		/*
		 * Wait for a connection request to arrive.
		 *
		 * We block all signals except while sleeping. That makes it safe for
		 * signal handlers, which again block all signals while executing, to
		 * do nontrivial work.
		 *
		 * If we are in PM_WAIT_DEAD_END state, then we don't want to accept
		 * any new connections, so we don't call select(), and just sleep.
		 */
		memcpy((char *) &rmask, (char *) &readmask, sizeof(fd_set));

		if (pmState == PM_WAIT_DEAD_END)
		{
			PG_SETMASK(&UnBlockSig);

			pg_usleep(100000L); /* 100 msec seems reasonable */
			selres = 0;

			PG_SETMASK(&BlockSig);
		}
		else
		{
			/* must set timeout each time; some OSes change it! */
			struct timeval timeout;

			/* Needs to run with blocked signals! */
			DetermineSleepTime(&timeout);

			PG_SETMASK(&UnBlockSig);

			selres = select(nSockets, &rmask, NULL, NULL, &timeout);

			PG_SETMASK(&BlockSig);
		}

		/* Now check the select() result */
		if (selres < 0)
		{
			if (errno != EINTR && errno != EWOULDBLOCK)
			{
				ereport(LOG,
						(errcode_for_socket_access(),
						 errmsg("select() failed in postmaster: %m")));
				return STATUS_ERROR;
			}
		}

		/*
		 * New connection pending on any of our sockets? If so, fork a child
		 * process to deal with it.
		 */
		if (selres > 0)
		{
			int			i;

			for (i = 0; i < MAXLISTEN; i++)
			{
				if (ListenSocket[i] == PGINVALID_SOCKET)
					break;
				if (FD_ISSET(ListenSocket[i], &rmask))
				{
					Port	   *port;

					port = ConnCreate(ListenSocket[i]);
					if (port)
					{
						BackendStartup(port);

						/*
						 * We no longer need the open socket or port structure
						 * in this process
						 */
						StreamClose(port->sock);
						ConnFree(port);
					}
				}
			}
		}

		/* If we have lost the log collector, try to start a new one */
		if (SysLoggerPID == 0 && Logging_collector)
			SysLoggerPID = SysLogger_Start();

		/*
		 * If no background writer process is running, and we are not in a
		 * state that prevents it, start one.  It doesn't matter if this
		 * fails, we'll just try again later.  Likewise for the checkpointer.
		 */
		if (pmState == PM_RUN || pmState == PM_RECOVERY ||
			pmState == PM_HOT_STANDBY)
		{
			if (CheckpointerPID == 0)
				CheckpointerPID = StartCheckpointer();
			if (BgWriterPID == 0)
				BgWriterPID = StartBackgroundWriter();
		}

		/*
		 * Likewise, if we have lost the walwriter process, try to start a new
		 * one.  But this is needed only in normal operation (else we cannot
		 * be writing any new WAL).
		 */
		if (WalWriterPID == 0 && pmState == PM_RUN)
			WalWriterPID = StartWalWriter();

		/*
		 * If we have lost the autovacuum launcher, try to start a new one. We
		 * don't want autovacuum to run in binary upgrade mode because
		 * autovacuum might update relfrozenxid for empty tables before the
		 * physical files are put in place.
		 */
		if (!IsBinaryUpgrade && AutoVacPID == 0 &&
			(AutoVacuumingActive() || start_autovac_launcher) &&
			pmState == PM_RUN)
		{
			AutoVacPID = StartAutoVacLauncher();
			if (AutoVacPID != 0)
				start_autovac_launcher = false; /* signal processed */
		}

		/* If we have lost the stats collector, try to start a new one */
		if (PgStatPID == 0 &&
			(pmState == PM_RUN || pmState == PM_HOT_STANDBY))
			PgStatPID = pgstat_start();

		/* If we have lost the archiver, try to start a new one. */
		if (PgArchPID == 0 && PgArchStartupAllowed())
			PgArchPID = pgarch_start();

		/* If we need to signal the autovacuum launcher, do so now */
		if (avlauncher_needs_signal)
		{
			avlauncher_needs_signal = false;
			if (AutoVacPID != 0)
				kill(AutoVacPID, SIGUSR2);
		}

		/* If we need to start a WAL receiver, try to do that now */
		if (WalReceiverRequested)
			MaybeStartWalReceiver();

		/* Get other worker processes running, if needed */
		if (StartWorkerNeeded || HaveCrashedWorker)
			maybe_start_bgworkers();

#ifdef HAVE_PTHREAD_IS_THREADED_NP

		/*
		 * With assertions enabled, check regularly for appearance of
		 * additional threads.  All builds check at start and exit.
		 */
		Assert(pthread_is_threaded_np() == 0);
#endif

		/*
		 * Lastly, check to see if it's time to do some things that we don't
		 * want to do every single time through the loop, because they're a
		 * bit expensive.  Note that there's up to a minute of slop in when
		 * these tasks will be performed, since DetermineSleepTime() will let
		 * us sleep at most that long; except for SIGKILL timeout which has
		 * special-case logic there.
		 */
		now = time(NULL);

		/*
		 * If we already sent SIGQUIT to children and they are slow to shut
		 * down, it's time to send them SIGKILL.  This doesn't happen
		 * normally, but under certain conditions backends can get stuck while
		 * shutting down.  This is a last measure to get them unwedged.
		 *
		 * Note we also do this during recovery from a process crash.
		 */
		if ((Shutdown >= ImmediateShutdown || (FatalError && !SendStop)) &&
			AbortStartTime != 0 &&
			(now - AbortStartTime) >= SIGKILL_CHILDREN_AFTER_SECS)
		{
			/* We were gentle with them before. Not anymore */
			TerminateChildren(SIGKILL);
			/* reset flag so we don't SIGKILL again */
			AbortStartTime = 0;
		}

		/*
		 * Once a minute, verify that postmaster.pid hasn't been removed or
		 * overwritten.  If it has, we force a shutdown.  This avoids having
		 * postmasters and child processes hanging around after their database
		 * is gone, and maybe causing problems if a new database cluster is
		 * created in the same place.  It also provides some protection
		 * against a DBA foolishly removing postmaster.pid and manually
		 * starting a new postmaster.  Data corruption is likely to ensue from
		 * that anyway, but we can minimize the damage by aborting ASAP.
		 */
		if (now - last_lockfile_recheck_time >= 1 * SECS_PER_MINUTE)
		{
			if (!RecheckDataDirLockFile())
			{
				ereport(LOG,
						(errmsg("performing immediate shutdown because data directory lock file is invalid")));
				kill(MyProcPid, SIGQUIT);
			}
			last_lockfile_recheck_time = now;
		}

		/*
		 * Touch Unix socket and lock files every 58 minutes, to ensure that
		 * they are not removed by overzealous /tmp-cleaning tasks.  We assume
		 * no one runs cleaners with cutoff times of less than an hour ...
		 */
		if (now - last_touch_time >= 58 * SECS_PER_MINUTE)
		{
			TouchSocketFiles();
			TouchSocketLockFiles();
			last_touch_time = now;
		}
	}
}