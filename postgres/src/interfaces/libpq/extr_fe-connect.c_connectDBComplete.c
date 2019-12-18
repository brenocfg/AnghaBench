#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct addrinfo {int dummy; } ;
struct TYPE_6__ {scalar_t__ status; int whichhost; int try_next_addr; int /*<<< orphan*/  errorMessage; struct addrinfo* addr_cur; int /*<<< orphan*/ * connect_timeout; } ;
typedef  int PostgresPollingStatusType ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ CONNECTION_NEEDED ; 
#define  PGRES_POLLING_OK 130 
#define  PGRES_POLLING_READING 129 
#define  PGRES_POLLING_WRITING 128 
 int PQconnectPoll (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_int_param (int /*<<< orphan*/ *,int*,TYPE_1__*,char*) ; 
 int pqWaitTimed (int,int,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
connectDBComplete(PGconn *conn)
{
	PostgresPollingStatusType flag = PGRES_POLLING_WRITING;
	time_t		finish_time = ((time_t) -1);
	int			timeout = 0;
	int			last_whichhost = -2;	/* certainly different from whichhost */
	struct addrinfo *last_addr_cur = NULL;

	if (conn == NULL || conn->status == CONNECTION_BAD)
		return 0;

	/*
	 * Set up a time limit, if connect_timeout isn't zero.
	 */
	if (conn->connect_timeout != NULL)
	{
		if (!parse_int_param(conn->connect_timeout, &timeout, conn,
							 "connect_timeout"))
		{
			/* mark the connection as bad to report the parsing failure */
			conn->status = CONNECTION_BAD;
			return 0;
		}

		if (timeout > 0)
		{
			/*
			 * Rounding could cause connection to fail unexpectedly quickly;
			 * to prevent possibly waiting hardly-at-all, insist on at least
			 * two seconds.
			 */
			if (timeout < 2)
				timeout = 2;
		}
		else					/* negative means 0 */
			timeout = 0;
	}

	for (;;)
	{
		int			ret = 0;

		/*
		 * (Re)start the connect_timeout timer if it's active and we are
		 * considering a different host than we were last time through.  If
		 * we've already succeeded, though, needn't recalculate.
		 */
		if (flag != PGRES_POLLING_OK &&
			timeout > 0 &&
			(conn->whichhost != last_whichhost ||
			 conn->addr_cur != last_addr_cur))
		{
			finish_time = time(NULL) + timeout;
			last_whichhost = conn->whichhost;
			last_addr_cur = conn->addr_cur;
		}

		/*
		 * Wait, if necessary.  Note that the initial state (just after
		 * PQconnectStart) is to wait for the socket to select for writing.
		 */
		switch (flag)
		{
			case PGRES_POLLING_OK:

				/*
				 * Reset stored error messages since we now have a working
				 * connection
				 */
				resetPQExpBuffer(&conn->errorMessage);
				return 1;		/* success! */

			case PGRES_POLLING_READING:
				ret = pqWaitTimed(1, 0, conn, finish_time);
				if (ret == -1)
				{
					/* hard failure, eg select() problem, aborts everything */
					conn->status = CONNECTION_BAD;
					return 0;
				}
				break;

			case PGRES_POLLING_WRITING:
				ret = pqWaitTimed(0, 1, conn, finish_time);
				if (ret == -1)
				{
					/* hard failure, eg select() problem, aborts everything */
					conn->status = CONNECTION_BAD;
					return 0;
				}
				break;

			default:
				/* Just in case we failed to set it in PQconnectPoll */
				conn->status = CONNECTION_BAD;
				return 0;
		}

		if (ret == 1)			/* connect_timeout elapsed */
		{
			/*
			 * Give up on current server/address, try the next one.
			 */
			conn->try_next_addr = true;
			conn->status = CONNECTION_NEEDED;
		}

		/*
		 * Now try to advance the state machine.
		 */
		flag = PQconnectPoll(conn);
	}
}