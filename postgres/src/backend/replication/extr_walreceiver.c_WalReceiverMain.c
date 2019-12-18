#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  standby_sysid ;
typedef  scalar_t__ pgsocket ;
typedef  int XLogRecPtr ;
struct TYPE_9__ {char* startpointTLI; } ;
struct TYPE_10__ {TYPE_1__ physical; } ;
struct TYPE_11__ {int logical; int startpoint; char* slotname; TYPE_2__ proto; } ;
typedef  TYPE_3__ WalRcvStreamOptions ;
struct TYPE_12__ {scalar_t__ pid; int walRcvState; int ready_to_display; int receiveStart; char* receiveStartTLI; int sender_port; int force_reply; int /*<<< orphan*/ * latch; int /*<<< orphan*/  mutex; scalar_t__ sender_host; scalar_t__ conninfo; scalar_t__ latestWalEndTime; scalar_t__ lastMsgReceiptTime; scalar_t__ lastMsgSendTime; scalar_t__ slotname; } ;
typedef  TYPE_4__ WalRcvData ;
typedef  scalar_t__ TimestampTz ;
typedef  char* TimeLineID ;
struct TYPE_14__ {int Write; int Flush; } ;
struct TYPE_13__ {int /*<<< orphan*/  procLatch; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_MODE_ALWAYS ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BlockSig ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ GetCurrentTimestamp () ; 
 int /*<<< orphan*/  GetSystemIdentifier () ; 
 int GetXLogReplayRecPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_8__ LogstreamResult ; 
 int MAXCONNINFO ; 
 int MAXFNAMELEN ; 
 TYPE_7__* MyProc ; 
 scalar_t__ MyProcPid ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NAPTIME_PER_CYCLE ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessWalRcvInterrupts () ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 char* ThisTimeLineID ; 
 scalar_t__ TimestampTzPlusMilliseconds (scalar_t__,int) ; 
 char* UINT64_FORMAT ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_RECEIVER_MAIN ; 
#define  WALRCV_RESTARTING 133 
#define  WALRCV_STARTING 132 
#define  WALRCV_STOPPED 131 
#define  WALRCV_STOPPING 130 
#define  WALRCV_STREAMING 129 
#define  WALRCV_WAITING 128 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_SOCKET_READABLE ; 
 int WL_TIMEOUT ; 
 int WaitLatchOrSocket (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* WalRcv ; 
 int /*<<< orphan*/  WalRcvDie ; 
 int /*<<< orphan*/  WalRcvFetchTimeLineHistoryFiles (char*,char*) ; 
 int /*<<< orphan*/  WalRcvQuickDieHandler ; 
 int /*<<< orphan*/  WalRcvShutdownHandler ; 
 int /*<<< orphan*/  WalRcvSigHupHandler ; 
 int /*<<< orphan*/  WalRcvSigUsr1Handler ; 
 int /*<<< orphan*/  WalRcvWaitForStartPosition (int*,char**) ; 
 int /*<<< orphan*/ * WalReceiverFunctions ; 
 int /*<<< orphan*/  XLogArchiveForceDone (char*) ; 
 scalar_t__ XLogArchiveMode ; 
 int /*<<< orphan*/  XLogArchiveNotify (char*) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* XLogFileNameP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogWalRcvFlush (int) ; 
 int /*<<< orphan*/  XLogWalRcvProcessMsg (char,char*,int) ; 
 int /*<<< orphan*/  XLogWalRcvSendHSFeedback (int) ; 
 int /*<<< orphan*/  XLogWalRcvSendReply (int,int) ; 
 scalar_t__ close (int) ; 
 char* cluster_name ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail (char*,char*,char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int got_SIGHUP ; 
 int /*<<< orphan*/  incoming_message ; 
 int /*<<< orphan*/  initStringInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_file (char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_memory_barrier () ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 int recvFile ; 
 int /*<<< orphan*/  recvFileTLI ; 
 int /*<<< orphan*/  recvSegNo ; 
 int /*<<< orphan*/  reply_message ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int wal_receiver_timeout ; 
 int /*<<< orphan*/  wal_segment_size ; 
 int /*<<< orphan*/  walrcv_connect (char*,int,char*,char**) ; 
 int /*<<< orphan*/  walrcv_endstreaming (int /*<<< orphan*/ ,char**) ; 
 char* walrcv_get_conninfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walrcv_get_senderinfo (int /*<<< orphan*/ ,char**,int*) ; 
 char* walrcv_identify_system (int /*<<< orphan*/ ,char**) ; 
 int walrcv_receive (int /*<<< orphan*/ ,char**,scalar_t__*) ; 
 scalar_t__ walrcv_startstreaming (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wrconn ; 

void
WalReceiverMain(void)
{
	char		conninfo[MAXCONNINFO];
	char	   *tmp_conninfo;
	char		slotname[NAMEDATALEN];
	XLogRecPtr	startpoint;
	TimeLineID	startpointTLI;
	TimeLineID	primaryTLI;
	bool		first_stream;
	WalRcvData *walrcv = WalRcv;
	TimestampTz last_recv_timestamp;
	TimestampTz now;
	bool		ping_sent;
	char	   *err;
	char	   *sender_host = NULL;
	int			sender_port = 0;

	/*
	 * WalRcv should be set up already (if we are a backend, we inherit this
	 * by fork() or EXEC_BACKEND mechanism from the postmaster).
	 */
	Assert(walrcv != NULL);

	now = GetCurrentTimestamp();

	/*
	 * Mark walreceiver as running in shared memory.
	 *
	 * Do this as early as possible, so that if we fail later on, we'll set
	 * state to STOPPED. If we die before this, the startup process will keep
	 * waiting for us to start up, until it times out.
	 */
	SpinLockAcquire(&walrcv->mutex);
	Assert(walrcv->pid == 0);
	switch (walrcv->walRcvState)
	{
		case WALRCV_STOPPING:
			/* If we've already been requested to stop, don't start up. */
			walrcv->walRcvState = WALRCV_STOPPED;
			/* fall through */

		case WALRCV_STOPPED:
			SpinLockRelease(&walrcv->mutex);
			proc_exit(1);
			break;

		case WALRCV_STARTING:
			/* The usual case */
			break;

		case WALRCV_WAITING:
		case WALRCV_STREAMING:
		case WALRCV_RESTARTING:
		default:
			/* Shouldn't happen */
			SpinLockRelease(&walrcv->mutex);
			elog(PANIC, "walreceiver still running according to shared memory state");
	}
	/* Advertise our PID so that the startup process can kill us */
	walrcv->pid = MyProcPid;
	walrcv->walRcvState = WALRCV_STREAMING;

	/* Fetch information required to start streaming */
	walrcv->ready_to_display = false;
	strlcpy(conninfo, (char *) walrcv->conninfo, MAXCONNINFO);
	strlcpy(slotname, (char *) walrcv->slotname, NAMEDATALEN);
	startpoint = walrcv->receiveStart;
	startpointTLI = walrcv->receiveStartTLI;

	/* Initialise to a sanish value */
	walrcv->lastMsgSendTime =
		walrcv->lastMsgReceiptTime = walrcv->latestWalEndTime = now;

	/* Report the latch to use to awaken this process */
	walrcv->latch = &MyProc->procLatch;

	SpinLockRelease(&walrcv->mutex);

	/* Arrange to clean up at walreceiver exit */
	on_shmem_exit(WalRcvDie, 0);

	/* Properly accept or ignore signals the postmaster might send us */
	pqsignal(SIGHUP, WalRcvSigHupHandler);	/* set flag to read config file */
	pqsignal(SIGINT, SIG_IGN);
	pqsignal(SIGTERM, WalRcvShutdownHandler);	/* request shutdown */
	pqsignal(SIGQUIT, WalRcvQuickDieHandler);	/* hard crash time */
	pqsignal(SIGALRM, SIG_IGN);
	pqsignal(SIGPIPE, SIG_IGN);
	pqsignal(SIGUSR1, WalRcvSigUsr1Handler);
	pqsignal(SIGUSR2, SIG_IGN);

	/* Reset some signals that are accepted by postmaster but not here */
	pqsignal(SIGCHLD, SIG_DFL);

	/* We allow SIGQUIT (quickdie) at all times */
	sigdelset(&BlockSig, SIGQUIT);

	/* Load the libpq-specific functions */
	load_file("libpqwalreceiver", false);
	if (WalReceiverFunctions == NULL)
		elog(ERROR, "libpqwalreceiver didn't initialize correctly");

	/* Unblock signals (they were blocked when the postmaster forked us) */
	PG_SETMASK(&UnBlockSig);

	/* Establish the connection to the primary for XLOG streaming */
	wrconn = walrcv_connect(conninfo, false, cluster_name[0] ? cluster_name : "walreceiver", &err);
	if (!wrconn)
		ereport(ERROR,
				(errmsg("could not connect to the primary server: %s", err)));

	/*
	 * Save user-visible connection string.  This clobbers the original
	 * conninfo, for security. Also save host and port of the sender server
	 * this walreceiver is connected to.
	 */
	tmp_conninfo = walrcv_get_conninfo(wrconn);
	walrcv_get_senderinfo(wrconn, &sender_host, &sender_port);
	SpinLockAcquire(&walrcv->mutex);
	memset(walrcv->conninfo, 0, MAXCONNINFO);
	if (tmp_conninfo)
		strlcpy((char *) walrcv->conninfo, tmp_conninfo, MAXCONNINFO);

	memset(walrcv->sender_host, 0, NI_MAXHOST);
	if (sender_host)
		strlcpy((char *) walrcv->sender_host, sender_host, NI_MAXHOST);

	walrcv->sender_port = sender_port;
	walrcv->ready_to_display = true;
	SpinLockRelease(&walrcv->mutex);

	if (tmp_conninfo)
		pfree(tmp_conninfo);

	if (sender_host)
		pfree(sender_host);

	first_stream = true;
	for (;;)
	{
		char	   *primary_sysid;
		char		standby_sysid[32];
		WalRcvStreamOptions options;

		/*
		 * Check that we're connected to a valid server using the
		 * IDENTIFY_SYSTEM replication command.
		 */
		primary_sysid = walrcv_identify_system(wrconn, &primaryTLI);

		snprintf(standby_sysid, sizeof(standby_sysid), UINT64_FORMAT,
				 GetSystemIdentifier());
		if (strcmp(primary_sysid, standby_sysid) != 0)
		{
			ereport(ERROR,
					(errmsg("database system identifier differs between the primary and standby"),
					 errdetail("The primary's identifier is %s, the standby's identifier is %s.",
							   primary_sysid, standby_sysid)));
		}

		/*
		 * Confirm that the current timeline of the primary is the same or
		 * ahead of ours.
		 */
		if (primaryTLI < startpointTLI)
			ereport(ERROR,
					(errmsg("highest timeline %u of the primary is behind recovery timeline %u",
							primaryTLI, startpointTLI)));

		/*
		 * Get any missing history files. We do this always, even when we're
		 * not interested in that timeline, so that if we're promoted to
		 * become the master later on, we don't select the same timeline that
		 * was already used in the current master. This isn't bullet-proof -
		 * you'll need some external software to manage your cluster if you
		 * need to ensure that a unique timeline id is chosen in every case,
		 * but let's avoid the confusion of timeline id collisions where we
		 * can.
		 */
		WalRcvFetchTimeLineHistoryFiles(startpointTLI, primaryTLI);

		/*
		 * Start streaming.
		 *
		 * We'll try to start at the requested starting point and timeline,
		 * even if it's different from the server's latest timeline. In case
		 * we've already reached the end of the old timeline, the server will
		 * finish the streaming immediately, and we will go back to await
		 * orders from the startup process. If recovery_target_timeline is
		 * 'latest', the startup process will scan pg_wal and find the new
		 * history file, bump recovery target timeline, and ask us to restart
		 * on the new timeline.
		 */
		options.logical = false;
		options.startpoint = startpoint;
		options.slotname = slotname[0] != '\0' ? slotname : NULL;
		options.proto.physical.startpointTLI = startpointTLI;
		ThisTimeLineID = startpointTLI;
		if (walrcv_startstreaming(wrconn, &options))
		{
			if (first_stream)
				ereport(LOG,
						(errmsg("started streaming WAL from primary at %X/%X on timeline %u",
								(uint32) (startpoint >> 32), (uint32) startpoint,
								startpointTLI)));
			else
				ereport(LOG,
						(errmsg("restarted WAL streaming at %X/%X on timeline %u",
								(uint32) (startpoint >> 32), (uint32) startpoint,
								startpointTLI)));
			first_stream = false;

			/* Initialize LogstreamResult and buffers for processing messages */
			LogstreamResult.Write = LogstreamResult.Flush = GetXLogReplayRecPtr(NULL);
			initStringInfo(&reply_message);
			initStringInfo(&incoming_message);

			/* Initialize the last recv timestamp */
			last_recv_timestamp = GetCurrentTimestamp();
			ping_sent = false;

			/* Loop until end-of-streaming or error */
			for (;;)
			{
				char	   *buf;
				int			len;
				bool		endofwal = false;
				pgsocket	wait_fd = PGINVALID_SOCKET;
				int			rc;

				/*
				 * Exit walreceiver if we're not in recovery. This should not
				 * happen, but cross-check the status here.
				 */
				if (!RecoveryInProgress())
					ereport(FATAL,
							(errmsg("cannot continue WAL streaming, recovery has already ended")));

				/* Process any requests or signals received recently */
				ProcessWalRcvInterrupts();

				if (got_SIGHUP)
				{
					got_SIGHUP = false;
					ProcessConfigFile(PGC_SIGHUP);
					XLogWalRcvSendHSFeedback(true);
				}

				/* See if we can read data immediately */
				len = walrcv_receive(wrconn, &buf, &wait_fd);
				if (len != 0)
				{
					/*
					 * Process the received data, and any subsequent data we
					 * can read without blocking.
					 */
					for (;;)
					{
						if (len > 0)
						{
							/*
							 * Something was received from master, so reset
							 * timeout
							 */
							last_recv_timestamp = GetCurrentTimestamp();
							ping_sent = false;
							XLogWalRcvProcessMsg(buf[0], &buf[1], len - 1);
						}
						else if (len == 0)
							break;
						else if (len < 0)
						{
							ereport(LOG,
									(errmsg("replication terminated by primary server"),
									 errdetail("End of WAL reached on timeline %u at %X/%X.",
											   startpointTLI,
											   (uint32) (LogstreamResult.Write >> 32), (uint32) LogstreamResult.Write)));
							endofwal = true;
							break;
						}
						len = walrcv_receive(wrconn, &buf, &wait_fd);
					}

					/* Let the master know that we received some data. */
					XLogWalRcvSendReply(false, false);

					/*
					 * If we've written some records, flush them to disk and
					 * let the startup process and primary server know about
					 * them.
					 */
					XLogWalRcvFlush(false);
				}

				/* Check if we need to exit the streaming loop. */
				if (endofwal)
					break;

				/*
				 * Ideally we would reuse a WaitEventSet object repeatedly
				 * here to avoid the overheads of WaitLatchOrSocket on epoll
				 * systems, but we can't be sure that libpq (or any other
				 * walreceiver implementation) has the same socket (even if
				 * the fd is the same number, it may have been closed and
				 * reopened since the last time).  In future, if there is a
				 * function for removing sockets from WaitEventSet, then we
				 * could add and remove just the socket each time, potentially
				 * avoiding some system calls.
				 */
				Assert(wait_fd != PGINVALID_SOCKET);
				rc = WaitLatchOrSocket(walrcv->latch,
									   WL_EXIT_ON_PM_DEATH | WL_SOCKET_READABLE |
									   WL_TIMEOUT | WL_LATCH_SET,
									   wait_fd,
									   NAPTIME_PER_CYCLE,
									   WAIT_EVENT_WAL_RECEIVER_MAIN);
				if (rc & WL_LATCH_SET)
				{
					ResetLatch(walrcv->latch);
					ProcessWalRcvInterrupts();

					if (walrcv->force_reply)
					{
						/*
						 * The recovery process has asked us to send apply
						 * feedback now.  Make sure the flag is really set to
						 * false in shared memory before sending the reply, so
						 * we don't miss a new request for a reply.
						 */
						walrcv->force_reply = false;
						pg_memory_barrier();
						XLogWalRcvSendReply(true, false);
					}
				}
				if (rc & WL_TIMEOUT)
				{
					/*
					 * We didn't receive anything new. If we haven't heard
					 * anything from the server for more than
					 * wal_receiver_timeout / 2, ping the server. Also, if
					 * it's been longer than wal_receiver_status_interval
					 * since the last update we sent, send a status update to
					 * the master anyway, to report any progress in applying
					 * WAL.
					 */
					bool		requestReply = false;

					/*
					 * Check if time since last receive from standby has
					 * reached the configured limit.
					 */
					if (wal_receiver_timeout > 0)
					{
						TimestampTz now = GetCurrentTimestamp();
						TimestampTz timeout;

						timeout =
							TimestampTzPlusMilliseconds(last_recv_timestamp,
														wal_receiver_timeout);

						if (now >= timeout)
							ereport(ERROR,
									(errmsg("terminating walreceiver due to timeout")));

						/*
						 * We didn't receive anything new, for half of
						 * receiver replication timeout. Ping the server.
						 */
						if (!ping_sent)
						{
							timeout = TimestampTzPlusMilliseconds(last_recv_timestamp,
																  (wal_receiver_timeout / 2));
							if (now >= timeout)
							{
								requestReply = true;
								ping_sent = true;
							}
						}
					}

					XLogWalRcvSendReply(requestReply, requestReply);
					XLogWalRcvSendHSFeedback(false);
				}
			}

			/*
			 * The backend finished streaming. Exit streaming COPY-mode from
			 * our side, too.
			 */
			walrcv_endstreaming(wrconn, &primaryTLI);

			/*
			 * If the server had switched to a new timeline that we didn't
			 * know about when we began streaming, fetch its timeline history
			 * file now.
			 */
			WalRcvFetchTimeLineHistoryFiles(startpointTLI, primaryTLI);
		}
		else
			ereport(LOG,
					(errmsg("primary server contains no more WAL on requested timeline %u",
							startpointTLI)));

		/*
		 * End of WAL reached on the requested timeline. Close the last
		 * segment, and await for new orders from the startup process.
		 */
		if (recvFile >= 0)
		{
			char		xlogfname[MAXFNAMELEN];

			XLogWalRcvFlush(false);
			if (close(recvFile) != 0)
				ereport(PANIC,
						(errcode_for_file_access(),
						 errmsg("could not close log segment %s: %m",
								XLogFileNameP(recvFileTLI, recvSegNo))));

			/*
			 * Create .done file forcibly to prevent the streamed segment from
			 * being archived later.
			 */
			XLogFileName(xlogfname, recvFileTLI, recvSegNo, wal_segment_size);
			if (XLogArchiveMode != ARCHIVE_MODE_ALWAYS)
				XLogArchiveForceDone(xlogfname);
			else
				XLogArchiveNotify(xlogfname);
		}
		recvFile = -1;

		elog(DEBUG1, "walreceiver ended streaming and awaits new instructions");
		WalRcvWaitForStartPosition(&startpoint, &startpointTLI);
	}
	/* not reached */
}