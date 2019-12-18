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
struct TYPE_3__ {int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;
typedef  scalar_t__ TimeLineID ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_OUT ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQendcopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 scalar_t__ PQflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQputCopyEnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * libpqrcv_PQgetResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strtoint32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
libpqrcv_endstreaming(WalReceiverConn *conn, TimeLineID *next_tli)
{
	PGresult   *res;

	/*
	 * Send copy-end message.  As in libpqrcv_PQexec, this could theoretically
	 * block, but the risk seems small.
	 */
	if (PQputCopyEnd(conn->streamConn, NULL) <= 0 ||
		PQflush(conn->streamConn))
		ereport(ERROR,
				(errmsg("could not send end-of-streaming message to primary: %s",
						pchomp(PQerrorMessage(conn->streamConn)))));

	*next_tli = 0;

	/*
	 * After COPY is finished, we should receive a result set indicating the
	 * next timeline's ID, or just CommandComplete if the server was shut
	 * down.
	 *
	 * If we had not yet received CopyDone from the backend, PGRES_COPY_OUT is
	 * also possible in case we aborted the copy in mid-stream.
	 */
	res = libpqrcv_PQgetResult(conn->streamConn);
	if (PQresultStatus(res) == PGRES_TUPLES_OK)
	{
		/*
		 * Read the next timeline's ID. The server also sends the timeline's
		 * starting point, but it is ignored.
		 */
		if (PQnfields(res) < 2 || PQntuples(res) != 1)
			ereport(ERROR,
					(errmsg("unexpected result set after end-of-streaming")));
		*next_tli = pg_strtoint32(PQgetvalue(res, 0, 0));
		PQclear(res);

		/* the result set should be followed by CommandComplete */
		res = libpqrcv_PQgetResult(conn->streamConn);
	}
	else if (PQresultStatus(res) == PGRES_COPY_OUT)
	{
		PQclear(res);

		/* End the copy */
		if (PQendcopy(conn->streamConn))
			ereport(ERROR,
					(errmsg("error while shutting down streaming COPY: %s",
							pchomp(PQerrorMessage(conn->streamConn)))));

		/* CommandComplete should follow */
		res = libpqrcv_PQgetResult(conn->streamConn);
	}

	if (PQresultStatus(res) != PGRES_COMMAND_OK)
		ereport(ERROR,
				(errmsg("error reading result of streaming command: %s",
						pchomp(PQerrorMessage(conn->streamConn)))));
	PQclear(res);

	/* Verify that there are no more results */
	res = libpqrcv_PQgetResult(conn->streamConn);
	if (res != NULL)
		ereport(ERROR,
				(errmsg("unexpected result after CommandComplete: %s",
						pchomp(PQerrorMessage(conn->streamConn)))));
}