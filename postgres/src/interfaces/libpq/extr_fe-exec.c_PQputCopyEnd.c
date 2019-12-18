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
struct TYPE_8__ {scalar_t__ asyncStatus; scalar_t__ queryclass; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  pversion; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_BUSY ; 
 scalar_t__ PGASYNC_COPY_BOTH ; 
 scalar_t__ PGASYNC_COPY_IN ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 scalar_t__ PGQUERY_SIMPLE ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_1__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_1__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_1__*) ; 
 scalar_t__ pqPutnchar (char*,int,TYPE_1__*) ; 
 scalar_t__ pqPuts (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

int
PQputCopyEnd(PGconn *conn, const char *errormsg)
{
	if (!conn)
		return -1;
	if (conn->asyncStatus != PGASYNC_COPY_IN &&
		conn->asyncStatus != PGASYNC_COPY_BOTH)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no COPY in progress\n"));
		return -1;
	}

	/*
	 * Send the COPY END indicator.  This is simple enough that we don't
	 * bother delegating it to the fe-protocol files.
	 */
	if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
	{
		if (errormsg)
		{
			/* Send COPY FAIL */
			if (pqPutMsgStart('f', false, conn) < 0 ||
				pqPuts(errormsg, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
		else
		{
			/* Send COPY DONE */
			if (pqPutMsgStart('c', false, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}

		/*
		 * If we sent the COPY command in extended-query mode, we must issue a
		 * Sync as well.
		 */
		if (conn->queryclass != PGQUERY_SIMPLE)
		{
			if (pqPutMsgStart('S', false, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
	}
	else
	{
		if (errormsg)
		{
			/* Oops, no way to do this in 2.0 */
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("function requires at least protocol version 3.0\n"));
			return -1;
		}
		else
		{
			/* Send old-style end-of-data marker */
			if (pqPutMsgStart(0, false, conn) < 0 ||
				pqPutnchar("\\.\n", 3, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
	}

	/* Return to active duty */
	if (conn->asyncStatus == PGASYNC_COPY_BOTH)
		conn->asyncStatus = PGASYNC_COPY_OUT;
	else
		conn->asyncStatus = PGASYNC_BUSY;
	resetPQExpBuffer(&conn->errorMessage);

	/* Try to flush data */
	if (pqFlush(conn) < 0)
		return -1;

	return 1;
}