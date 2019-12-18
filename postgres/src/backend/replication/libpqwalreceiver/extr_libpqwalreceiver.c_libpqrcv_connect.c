#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  keys ;
struct TYPE_4__ {int logical; int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;
typedef  scalar_t__ PostgresPollingStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ CONNECTION_STARTED ; 
 char* GetDatabaseEncodingName () ; 
 int /*<<< orphan*/  MyLatch ; 
 scalar_t__ PGRES_POLLING_FAILED ; 
 scalar_t__ PGRES_POLLING_OK ; 
 scalar_t__ PGRES_POLLING_READING ; 
 scalar_t__ PGRES_POLLING_WRITING ; 
 scalar_t__ PQconnectPoll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQconnectStartParams (char const**,char const**,int) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsocket (int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessWalRcvInterrupts () ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_LIBPQWALRECEIVER_CONNECT ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_SOCKET_CONNECTED ; 
 int WL_SOCKET_READABLE ; 
 int WL_SOCKET_WRITEABLE ; 
 int WaitLatchOrSocket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc0 (int) ; 
 char* pchomp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WalReceiverConn *
libpqrcv_connect(const char *conninfo, bool logical, const char *appname,
				 char **err)
{
	WalReceiverConn *conn;
	PostgresPollingStatusType status;
	const char *keys[5];
	const char *vals[5];
	int			i = 0;

	/*
	 * We use the expand_dbname parameter to process the connection string (or
	 * URI), and pass some extra options.
	 */
	keys[i] = "dbname";
	vals[i] = conninfo;
	keys[++i] = "replication";
	vals[i] = logical ? "database" : "true";
	if (!logical)
	{
		/*
		 * The database name is ignored by the server in replication mode, but
		 * specify "replication" for .pgpass lookup.
		 */
		keys[++i] = "dbname";
		vals[i] = "replication";
	}
	keys[++i] = "fallback_application_name";
	vals[i] = appname;
	if (logical)
	{
		keys[++i] = "client_encoding";
		vals[i] = GetDatabaseEncodingName();
	}
	keys[++i] = NULL;
	vals[i] = NULL;

	Assert(i < sizeof(keys));

	conn = palloc0(sizeof(WalReceiverConn));
	conn->streamConn = PQconnectStartParams(keys, vals,
											 /* expand_dbname = */ true);
	if (PQstatus(conn->streamConn) == CONNECTION_BAD)
	{
		*err = pchomp(PQerrorMessage(conn->streamConn));
		return NULL;
	}

	/*
	 * Poll connection until we have OK or FAILED status.
	 *
	 * Per spec for PQconnectPoll, first wait till socket is write-ready.
	 */
	status = PGRES_POLLING_WRITING;
	do
	{
		int			io_flag;
		int			rc;

		if (status == PGRES_POLLING_READING)
			io_flag = WL_SOCKET_READABLE;
#ifdef WIN32
		/* Windows needs a different test while waiting for connection-made */
		else if (PQstatus(conn->streamConn) == CONNECTION_STARTED)
			io_flag = WL_SOCKET_CONNECTED;
#endif
		else
			io_flag = WL_SOCKET_WRITEABLE;

		rc = WaitLatchOrSocket(MyLatch,
							   WL_EXIT_ON_PM_DEATH | WL_LATCH_SET | io_flag,
							   PQsocket(conn->streamConn),
							   0,
							   WAIT_EVENT_LIBPQWALRECEIVER_CONNECT);

		/* Interrupted? */
		if (rc & WL_LATCH_SET)
		{
			ResetLatch(MyLatch);
			ProcessWalRcvInterrupts();
		}

		/* If socket is ready, advance the libpq state machine */
		if (rc & io_flag)
			status = PQconnectPoll(conn->streamConn);
	} while (status != PGRES_POLLING_OK && status != PGRES_POLLING_FAILED);

	if (PQstatus(conn->streamConn) != CONNECTION_OK)
	{
		*err = pchomp(PQerrorMessage(conn->streamConn));
		return NULL;
	}

	conn->logical = logical;

	return conn;
}