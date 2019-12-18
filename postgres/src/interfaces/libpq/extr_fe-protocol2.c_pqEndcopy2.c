#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int len; char* data; } ;
struct TYPE_15__ {scalar_t__ asyncStatus; int /*<<< orphan*/  noticeHooks; TYPE_3__ errorMessage; } ;
struct TYPE_14__ {scalar_t__ resultStatus; } ;
typedef  TYPE_1__ PGresult ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_BUSY ; 
 scalar_t__ PGASYNC_COPY_IN ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (TYPE_1__*) ; 
 TYPE_1__* PQgetResult (TYPE_2__*) ; 
 scalar_t__ PQisBusy (TYPE_2__*) ; 
 int /*<<< orphan*/  PQreset (TYPE_2__*) ; 
 int /*<<< orphan*/  PQresetStart (TYPE_2__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_2__*) ; 
 int /*<<< orphan*/  pqInternalNotice (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ pqIsnonblocking (TYPE_2__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 

int
pqEndcopy2(PGconn *conn)
{
	PGresult   *result;

	if (conn->asyncStatus != PGASYNC_COPY_IN &&
		conn->asyncStatus != PGASYNC_COPY_OUT)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no COPY in progress\n"));
		return 1;
	}

	/*
	 * make sure no data is waiting to be sent, abort if we are non-blocking
	 * and the flush fails
	 */
	if (pqFlush(conn) && pqIsnonblocking(conn))
		return 1;

	/* non blocking connections may have to abort at this point. */
	if (pqIsnonblocking(conn) && PQisBusy(conn))
		return 1;

	/* Return to active duty */
	conn->asyncStatus = PGASYNC_BUSY;
	resetPQExpBuffer(&conn->errorMessage);

	/* Wait for the completion response */
	result = PQgetResult(conn);

	/* Expecting a successful result */
	if (result && result->resultStatus == PGRES_COMMAND_OK)
	{
		PQclear(result);
		return 0;
	}

	/*
	 * Trouble. For backwards-compatibility reasons, we issue the error
	 * message as if it were a notice (would be nice to get rid of this
	 * silliness, but too many apps probably don't handle errors from
	 * PQendcopy reasonably).  Note that the app can still obtain the error
	 * status from the PGconn object.
	 */
	if (conn->errorMessage.len > 0)
	{
		/* We have to strip the trailing newline ... pain in neck... */
		char		svLast = conn->errorMessage.data[conn->errorMessage.len - 1];

		if (svLast == '\n')
			conn->errorMessage.data[conn->errorMessage.len - 1] = '\0';
		pqInternalNotice(&conn->noticeHooks, "%s", conn->errorMessage.data);
		conn->errorMessage.data[conn->errorMessage.len - 1] = svLast;
	}

	PQclear(result);

	/*
	 * The worst case is that we've lost sync with the backend entirely due to
	 * application screwup of the copy in/out protocol. To recover, reset the
	 * connection (talk about using a sledgehammer...)
	 */
	pqInternalNotice(&conn->noticeHooks,
					 "lost synchronization with server, resetting connection");

	/*
	 * Users doing non-blocking connections need to handle the reset
	 * themselves, they'll need to check the connection status if we return an
	 * error.
	 */
	if (pqIsnonblocking(conn))
		PQresetStart(conn);
	else
		PQreset(conn);

	return 1;
}