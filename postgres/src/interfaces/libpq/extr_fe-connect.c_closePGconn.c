#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nonblocking; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  xactStatus; int /*<<< orphan*/  asyncStatus; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_BAD ; 
 int /*<<< orphan*/  PGASYNC_IDLE ; 
 int /*<<< orphan*/  PQTRANS_IDLE ; 
 int /*<<< orphan*/  pqClearAsyncResult (TYPE_1__*) ; 
 int /*<<< orphan*/  pqDropConnection (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pqDropServerData (TYPE_1__*) ; 
 int /*<<< orphan*/  release_conn_addrinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendTerminateConn (TYPE_1__*) ; 

__attribute__((used)) static void
closePGconn(PGconn *conn)
{
	/*
	 * If possible, send Terminate message to close the connection politely.
	 */
	sendTerminateConn(conn);

	/*
	 * Must reset the blocking status so a possible reconnect will work.
	 *
	 * Don't call PQsetnonblocking() because it will fail if it's unable to
	 * flush the connection.
	 */
	conn->nonblocking = false;

	/*
	 * Close the connection, reset all transient state, flush I/O buffers.
	 */
	pqDropConnection(conn, true);
	conn->status = CONNECTION_BAD;	/* Well, not really _bad_ - just absent */
	conn->asyncStatus = PGASYNC_IDLE;
	conn->xactStatus = PQTRANS_IDLE;
	pqClearAsyncResult(conn);	/* deallocate result */
	resetPQExpBuffer(&conn->errorMessage);
	release_conn_addrinfo(conn);

	/* Reset all state obtained from server, too */
	pqDropServerData(conn);
}