#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  remote_ps_data ;
typedef  int /*<<< orphan*/  remote_port ;
typedef  int /*<<< orphan*/  remote_host ;
struct TYPE_6__ {int /*<<< orphan*/  salen; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {char* remote_host; char* remote_port; int /*<<< orphan*/  database_name; int /*<<< orphan*/  user_name; void* remote_hostname; TYPE_1__ raddr; } ;
typedef  TYPE_2__ Port ;

/* Variables and functions */
 int AuthenticationTimeout ; 
 int /*<<< orphan*/  B_WAL_SENDER ; 
 int /*<<< orphan*/  BlockSig ; 
 int ClientAuthInProgress ; 
 int /*<<< orphan*/  DestRemote ; 
 int /*<<< orphan*/  InitializeTimeouts () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ Log_connections ; 
 TYPE_2__* MyProcPort ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 long PreAuthDelay ; 
 int ProcessStartupPacket (TYPE_2__*,int) ; 
 int /*<<< orphan*/  RegisterTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  STARTUP_PACKET_TIMEOUT ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  StartupBlockSig ; 
 int /*<<< orphan*/  StartupPacketTimeoutHandler ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ am_walsender ; 
 int /*<<< orphan*/  disable_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_timeout_after (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  init_ps_display (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ log_hostname ; 
 int pg_getnameinfo_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  pgstat_get_backend_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_init () ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  startup_die ; 
 void* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 
 scalar_t__ update_process_title ; 
 int /*<<< orphan*/  whereToSendOutput ; 

__attribute__((used)) static void
BackendInitialize(Port *port)
{
	int			status;
	int			ret;
	char		remote_host[NI_MAXHOST];
	char		remote_port[NI_MAXSERV];
	char		remote_ps_data[NI_MAXHOST];

	/* Save port etc. for ps status */
	MyProcPort = port;

	/*
	 * PreAuthDelay is a debugging aid for investigating problems in the
	 * authentication cycle: it can be set in postgresql.conf to allow time to
	 * attach to the newly-forked backend with a debugger.  (See also
	 * PostAuthDelay, which we allow clients to pass through PGOPTIONS, but it
	 * is not honored until after authentication.)
	 */
	if (PreAuthDelay > 0)
		pg_usleep(PreAuthDelay * 1000000L);

	/* This flag will remain set until InitPostgres finishes authentication */
	ClientAuthInProgress = true;	/* limit visibility of log messages */

	/* set these to empty in case they are needed before we set them up */
	port->remote_host = "";
	port->remote_port = "";

	/*
	 * Initialize libpq and enable reporting of ereport errors to the client.
	 * Must do this now because authentication uses libpq to send messages.
	 */
	pq_init();					/* initialize libpq to talk to client */
	whereToSendOutput = DestRemote; /* now safe to ereport to client */

	/*
	 * We arrange for a simple exit(1) if we receive SIGTERM or SIGQUIT or
	 * timeout while trying to collect the startup packet.  Otherwise the
	 * postmaster cannot shutdown the database FAST or IMMED cleanly if a
	 * buggy client fails to send the packet promptly.  XXX it follows that
	 * the remainder of this function must tolerate losing control at any
	 * instant.  Likewise, any pg_on_exit_callback registered before or during
	 * this function must be prepared to execute at any instant between here
	 * and the end of this function.  Furthermore, affected callbacks execute
	 * partially or not at all when a second exit-inducing signal arrives
	 * after proc_exit_prepare() decrements on_proc_exit_index.  (Thanks to
	 * that mechanic, callbacks need not anticipate more than one call.)  This
	 * is fragile; it ought to instead follow the norm of handling interrupts
	 * at selected, safe opportunities.
	 */
	pqsignal(SIGTERM, startup_die);
	pqsignal(SIGQUIT, startup_die);
	InitializeTimeouts();		/* establishes SIGALRM handler */
	PG_SETMASK(&StartupBlockSig);

	/*
	 * Get the remote host name and port for logging and status display.
	 */
	remote_host[0] = '\0';
	remote_port[0] = '\0';
	if ((ret = pg_getnameinfo_all(&port->raddr.addr, port->raddr.salen,
								  remote_host, sizeof(remote_host),
								  remote_port, sizeof(remote_port),
								  (log_hostname ? 0 : NI_NUMERICHOST) | NI_NUMERICSERV)) != 0)
		ereport(WARNING,
				(errmsg_internal("pg_getnameinfo_all() failed: %s",
								 gai_strerror(ret))));
	if (remote_port[0] == '\0')
		snprintf(remote_ps_data, sizeof(remote_ps_data), "%s", remote_host);
	else
		snprintf(remote_ps_data, sizeof(remote_ps_data), "%s(%s)", remote_host, remote_port);

	/*
	 * Save remote_host and remote_port in port structure (after this, they
	 * will appear in log_line_prefix data for log messages).
	 */
	port->remote_host = strdup(remote_host);
	port->remote_port = strdup(remote_port);

	/* And now we can issue the Log_connections message, if wanted */
	if (Log_connections)
	{
		if (remote_port[0])
			ereport(LOG,
					(errmsg("connection received: host=%s port=%s",
							remote_host,
							remote_port)));
		else
			ereport(LOG,
					(errmsg("connection received: host=%s",
							remote_host)));
	}

	/*
	 * If we did a reverse lookup to name, we might as well save the results
	 * rather than possibly repeating the lookup during authentication.
	 *
	 * Note that we don't want to specify NI_NAMEREQD above, because then we'd
	 * get nothing useful for a client without an rDNS entry.  Therefore, we
	 * must check whether we got a numeric IPv4 or IPv6 address, and not save
	 * it into remote_hostname if so.  (This test is conservative and might
	 * sometimes classify a hostname as numeric, but an error in that
	 * direction is safe; it only results in a possible extra lookup.)
	 */
	if (log_hostname &&
		ret == 0 &&
		strspn(remote_host, "0123456789.") < strlen(remote_host) &&
		strspn(remote_host, "0123456789ABCDEFabcdef:") < strlen(remote_host))
		port->remote_hostname = strdup(remote_host);

	/*
	 * Ready to begin client interaction.  We will give up and exit(1) after a
	 * time delay, so that a broken client can't hog a connection
	 * indefinitely.  PreAuthDelay and any DNS interactions above don't count
	 * against the time limit.
	 *
	 * Note: AuthenticationTimeout is applied here while waiting for the
	 * startup packet, and then again in InitPostgres for the duration of any
	 * authentication operations.  So a hostile client could tie up the
	 * process for nearly twice AuthenticationTimeout before we kick him off.
	 *
	 * Note: because PostgresMain will call InitializeTimeouts again, the
	 * registration of STARTUP_PACKET_TIMEOUT will be lost.  This is okay
	 * since we never use it again after this function.
	 */
	RegisterTimeout(STARTUP_PACKET_TIMEOUT, StartupPacketTimeoutHandler);
	enable_timeout_after(STARTUP_PACKET_TIMEOUT, AuthenticationTimeout * 1000);

	/*
	 * Receive the startup packet (which might turn out to be a cancel request
	 * packet).
	 */
	status = ProcessStartupPacket(port, false);

	/*
	 * Stop here if it was bad or a cancel packet.  ProcessStartupPacket
	 * already did any appropriate error reporting.
	 */
	if (status != STATUS_OK)
		proc_exit(0);

	/*
	 * Now that we have the user and database name, we can set the process
	 * title for ps.  It's good to do this as early as possible in startup.
	 *
	 * For a walsender, the ps display is set in the following form:
	 *
	 * postgres: walsender <user> <host> <activity>
	 *
	 * To achieve that, we pass "walsender" as username and username as dbname
	 * to init_ps_display(). XXX: should add a new variant of
	 * init_ps_display() to avoid abusing the parameters like this.
	 */
	if (am_walsender)
		init_ps_display(pgstat_get_backend_desc(B_WAL_SENDER), port->user_name, remote_ps_data,
						update_process_title ? "authentication" : "");
	else
		init_ps_display(port->user_name, port->database_name, remote_ps_data,
						update_process_title ? "authentication" : "");

	/*
	 * Disable the timeout, and prevent SIGTERM/SIGQUIT again.
	 */
	disable_timeout(STARTUP_PACKET_TIMEOUT, false);
	PG_SETMASK(&BlockSig);
}