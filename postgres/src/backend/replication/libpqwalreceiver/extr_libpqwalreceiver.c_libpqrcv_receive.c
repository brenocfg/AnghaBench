#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgsocket ;
struct TYPE_3__ {char* recvBuf; int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_IN ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQconsumeInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQsocket (int /*<<< orphan*/ ) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * libpqrcv_PQgetResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
libpqrcv_receive(WalReceiverConn *conn, char **buffer,
				 pgsocket *wait_fd)
{
	int			rawlen;

	if (conn->recvBuf != NULL)
		PQfreemem(conn->recvBuf);
	conn->recvBuf = NULL;

	/* Try to receive a CopyData message */
	rawlen = PQgetCopyData(conn->streamConn, &conn->recvBuf, 1);
	if (rawlen == 0)
	{
		/* Try consuming some data. */
		if (PQconsumeInput(conn->streamConn) == 0)
			ereport(ERROR,
					(errmsg("could not receive data from WAL stream: %s",
							pchomp(PQerrorMessage(conn->streamConn)))));

		/* Now that we've consumed some input, try again */
		rawlen = PQgetCopyData(conn->streamConn, &conn->recvBuf, 1);
		if (rawlen == 0)
		{
			/* Tell caller to try again when our socket is ready. */
			*wait_fd = PQsocket(conn->streamConn);
			return 0;
		}
	}
	if (rawlen == -1)			/* end-of-streaming or error */
	{
		PGresult   *res;

		res = libpqrcv_PQgetResult(conn->streamConn);
		if (PQresultStatus(res) == PGRES_COMMAND_OK)
		{
			PQclear(res);

			/* Verify that there are no more results. */
			res = libpqrcv_PQgetResult(conn->streamConn);
			if (res != NULL)
			{
				PQclear(res);

				/*
				 * If the other side closed the connection orderly (otherwise
				 * we'd seen an error, or PGRES_COPY_IN) don't report an error
				 * here, but let callers deal with it.
				 */
				if (PQstatus(conn->streamConn) == CONNECTION_BAD)
					return -1;

				ereport(ERROR,
						(errmsg("unexpected result after CommandComplete: %s",
								PQerrorMessage(conn->streamConn))));
			}

			return -1;
		}
		else if (PQresultStatus(res) == PGRES_COPY_IN)
		{
			PQclear(res);
			return -1;
		}
		else
		{
			PQclear(res);
			ereport(ERROR,
					(errmsg("could not receive data from WAL stream: %s",
							pchomp(PQerrorMessage(conn->streamConn)))));
		}
	}
	if (rawlen < -1)
		ereport(ERROR,
				(errmsg("could not receive data from WAL stream: %s",
						pchomp(PQerrorMessage(conn->streamConn)))));

	/* Return received messages to caller */
	*buffer = conn->recvBuf;
	return rawlen;
}