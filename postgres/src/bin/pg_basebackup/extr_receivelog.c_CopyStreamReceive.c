#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pgsocket ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int CopyStreamPoll (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ PQconsumeInput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
CopyStreamReceive(PGconn *conn, long timeout, pgsocket stop_socket,
				  char **buffer)
{
	char	   *copybuf = NULL;
	int			rawlen;

	if (*buffer != NULL)
		PQfreemem(*buffer);
	*buffer = NULL;

	/* Try to receive a CopyData message */
	rawlen = PQgetCopyData(conn, &copybuf, 1);
	if (rawlen == 0)
	{
		int			ret;

		/*
		 * No data available.  Wait for some to appear, but not longer than
		 * the specified timeout, so that we can ping the server.  Also stop
		 * waiting if input appears on stop_socket.
		 */
		ret = CopyStreamPoll(conn, timeout, stop_socket);
		if (ret <= 0)
			return ret;

		/* Now there is actually data on the socket */
		if (PQconsumeInput(conn) == 0)
		{
			pg_log_error("could not receive data from WAL stream: %s",
						 PQerrorMessage(conn));
			return -1;
		}

		/* Now that we've consumed some input, try again */
		rawlen = PQgetCopyData(conn, &copybuf, 1);
		if (rawlen == 0)
			return 0;
	}
	if (rawlen == -1)			/* end-of-streaming or error */
		return -2;
	if (rawlen == -2)
	{
		pg_log_error("could not read COPY data: %s", PQerrorMessage(conn));
		return -1;
	}

	/* Return received messages to caller */
	*buffer = copybuf;
	return rawlen;
}