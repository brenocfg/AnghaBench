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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 

bool
handleCopyOut(PGconn *conn, FILE *copystream, PGresult **res)
{
	bool		OK = true;
	char	   *buf;
	int			ret;

	for (;;)
	{
		ret = PQgetCopyData(conn, &buf, 0);

		if (ret < 0)
			break;				/* done or server/connection error */

		if (buf)
		{
			if (OK && copystream && fwrite(buf, 1, ret, copystream) != ret)
			{
				pg_log_error("could not write COPY data: %m");
				/* complain only once, keep reading data from server */
				OK = false;
			}
			PQfreemem(buf);
		}
	}

	if (OK && copystream && fflush(copystream))
	{
		pg_log_error("could not write COPY data: %m");
		OK = false;
	}

	if (ret == -2)
	{
		pg_log_error("COPY data transfer failed: %s", PQerrorMessage(conn));
		OK = false;
	}

	/*
	 * Check command status and return to normal libpq state.
	 *
	 * If for some reason libpq is still reporting PGRES_COPY_OUT state, we
	 * would like to forcibly exit that state, since our caller would be
	 * unable to distinguish that situation from reaching the next COPY in a
	 * command string that happened to contain two consecutive COPY TO STDOUT
	 * commands.  However, libpq provides no API for doing that, and in
	 * principle it's a libpq bug anyway if PQgetCopyData() returns -1 or -2
	 * but hasn't exited COPY_OUT state internally.  So we ignore the
	 * possibility here.
	 */
	*res = PQgetResult(conn);
	if (PQresultStatus(*res) != PGRES_COMMAND_OK)
	{
		pg_log_info("%s", PQerrorMessage(conn));
		OK = false;
	}

	return OK;
}