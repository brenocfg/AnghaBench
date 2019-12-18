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
struct TYPE_5__ {char* gssencmode; int try_gss; int whichhost; int try_next_addr; int try_next_host; int /*<<< orphan*/  status; int /*<<< orphan*/  errorMessage; scalar_t__ outCount; scalar_t__ inEnd; scalar_t__ inCursor; scalar_t__ inStart; int /*<<< orphan*/  options_valid; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_BAD ; 
 int /*<<< orphan*/  CONNECTION_NEEDED ; 
 scalar_t__ PGRES_POLLING_WRITING ; 
 scalar_t__ PQconnectPoll (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_link_canary_is_frontend () ; 
 int /*<<< orphan*/  pqDropConnection (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
connectDBStart(PGconn *conn)
{
	if (!conn)
		return 0;

	if (!conn->options_valid)
		goto connect_errReturn;

	/*
	 * Check for bad linking to backend-internal versions of src/common
	 * functions (see comments in link-canary.c for the reason we need this).
	 * Nobody but developers should see this message, so we don't bother
	 * translating it.
	 */
	if (!pg_link_canary_is_frontend())
	{
		printfPQExpBuffer(&conn->errorMessage,
						  "libpq is incorrectly linked to backend functions\n");
		goto connect_errReturn;
	}

	/* Ensure our buffers are empty */
	conn->inStart = conn->inCursor = conn->inEnd = 0;
	conn->outCount = 0;

	/*
	 * Ensure errorMessage is empty, too.  PQconnectPoll will append messages
	 * to it in the process of scanning for a working server.  Thus, if we
	 * fail to connect to multiple hosts, the final error message will include
	 * details about each failure.
	 */
	resetPQExpBuffer(&conn->errorMessage);

#ifdef ENABLE_GSS
	if (conn->gssencmode[0] == 'd') /* "disable" */
		conn->try_gss = false;
#endif

	/*
	 * Set up to try to connect to the first host.  (Setting whichhost = -1 is
	 * a bit of a cheat, but PQconnectPoll will advance it to 0 before
	 * anything else looks at it.)
	 */
	conn->whichhost = -1;
	conn->try_next_addr = false;
	conn->try_next_host = true;
	conn->status = CONNECTION_NEEDED;

	/*
	 * The code for processing CONNECTION_NEEDED state is in PQconnectPoll(),
	 * so that it can easily be re-executed if needed again during the
	 * asynchronous startup process.  However, we must run it once here,
	 * because callers expect a success return from this routine to mean that
	 * we are in PGRES_POLLING_WRITING connection state.
	 */
	if (PQconnectPoll(conn) == PGRES_POLLING_WRITING)
		return 1;

connect_errReturn:

	/*
	 * If we managed to open a socket, close it immediately rather than
	 * waiting till PQfinish.  (The application cannot have gotten the socket
	 * from PQsocket yet, so this doesn't risk breaking anything.)
	 */
	pqDropConnection(conn, true);
	conn->status = CONNECTION_BAD;
	return 0;
}