#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ asyncStatus; int outBufSize; int outCount; int /*<<< orphan*/  pversion; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_COPY_BOTH ; 
 scalar_t__ PGASYNC_COPY_IN ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  parseInput (TYPE_1__*) ; 
 scalar_t__ pqCheckOutBufferSpace (int,TYPE_1__*) ; 
 scalar_t__ pqFlush (TYPE_1__*) ; 
 scalar_t__ pqIsnonblocking (TYPE_1__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_1__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_1__*) ; 
 scalar_t__ pqPutnchar (char const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
PQputCopyData(PGconn *conn, const char *buffer, int nbytes)
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
	 * Process any NOTICE or NOTIFY messages that might be pending in the
	 * input buffer.  Since the server might generate many notices during the
	 * COPY, we want to clean those out reasonably promptly to prevent
	 * indefinite expansion of the input buffer.  (Note: the actual read of
	 * input data into the input buffer happens down inside pqSendSome, but
	 * it's not authorized to get rid of the data again.)
	 */
	parseInput(conn);

	if (nbytes > 0)
	{
		/*
		 * Try to flush any previously sent data in preference to growing the
		 * output buffer.  If we can't enlarge the buffer enough to hold the
		 * data, return 0 in the nonblock case, else hard error. (For
		 * simplicity, always assume 5 bytes of overhead even in protocol 2.0
		 * case.)
		 */
		if ((conn->outBufSize - conn->outCount - 5) < nbytes)
		{
			if (pqFlush(conn) < 0)
				return -1;
			if (pqCheckOutBufferSpace(conn->outCount + 5 + (size_t) nbytes,
									  conn))
				return pqIsnonblocking(conn) ? 0 : -1;
		}
		/* Send the data (too simple to delegate to fe-protocol files) */
		if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
		{
			if (pqPutMsgStart('d', false, conn) < 0 ||
				pqPutnchar(buffer, nbytes, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
		else
		{
			if (pqPutMsgStart(0, false, conn) < 0 ||
				pqPutnchar(buffer, nbytes, conn) < 0 ||
				pqPutMsgEnd(conn) < 0)
				return -1;
		}
	}
	return 1;
}