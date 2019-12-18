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
struct TYPE_15__ {scalar_t__ asyncStatus; scalar_t__ queryclass; TYPE_3__ errorMessage; int /*<<< orphan*/  noticeHooks; } ;
struct TYPE_14__ {scalar_t__ resultStatus; } ;
typedef  TYPE_1__ PGresult ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_BUSY ; 
 scalar_t__ PGASYNC_COPY_BOTH ; 
 scalar_t__ PGASYNC_COPY_IN ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 scalar_t__ PGQUERY_SIMPLE ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (TYPE_1__*) ; 
 TYPE_1__* PQgetResult (TYPE_2__*) ; 
 scalar_t__ PQisBusy (TYPE_2__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_2__*) ; 
 int /*<<< orphan*/  pqInternalNotice (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ pqIsnonblocking (TYPE_2__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_2__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_2__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 

int
pqEndcopy3(PGconn *conn)
{
	PGresult   *result;

	if (conn->asyncStatus != PGASYNC_COPY_IN &&
		conn->asyncStatus != PGASYNC_COPY_OUT &&
		conn->asyncStatus != PGASYNC_COPY_BOTH)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no COPY in progress\n"));
		return 1;
	}

	/* Send the CopyDone message if needed */
	if (conn->asyncStatus == PGASYNC_COPY_IN ||
		conn->asyncStatus == PGASYNC_COPY_BOTH)
	{
		if (pqPutMsgStart('c', false, conn) < 0 ||
			pqPutMsgEnd(conn) < 0)
			return 1;

		/*
		 * If we sent the COPY command in extended-query mode, we must issue a
		 * Sync as well.
		 */
		if (conn->queryclass != PGQUERY_SIMPLE)
		{
			if (pqPutMsgStart('S', false, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return 1;
		}
	}

	/*
	 * make sure no data is waiting to be sent, abort if we are non-blocking
	 * and the flush fails
	 */
	if (pqFlush(conn) && pqIsnonblocking(conn))
		return 1;

	/* Return to active duty */
	conn->asyncStatus = PGASYNC_BUSY;
	resetPQExpBuffer(&conn->errorMessage);

	/*
	 * Non blocking connections may have to abort at this point.  If everyone
	 * played the game there should be no problem, but in error scenarios the
	 * expected messages may not have arrived yet.  (We are assuming that the
	 * backend's packetizing will ensure that CommandComplete arrives along
	 * with the CopyDone; are there corner cases where that doesn't happen?)
	 */
	if (pqIsnonblocking(conn) && PQisBusy(conn))
		return 1;

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

	return 1;
}