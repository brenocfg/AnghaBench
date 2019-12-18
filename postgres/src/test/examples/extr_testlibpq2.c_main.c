#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {char* relname; int be_pid; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ PGnotify ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQconnectdb (char const*) ; 
 int /*<<< orphan*/  PQconsumeInput (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (TYPE_1__*) ; 
 TYPE_1__* PQnotifies (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQsocket (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit_nicely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	const char *conninfo;
	PGconn	   *conn;
	PGresult   *res;
	PGnotify   *notify;
	int			nnotifies;

	/*
	 * If the user supplies a parameter on the command line, use it as the
	 * conninfo string; otherwise default to setting dbname=postgres and using
	 * environment variables or defaults for all other connection parameters.
	 */
	if (argc > 1)
		conninfo = argv[1];
	else
		conninfo = "dbname = postgres";

	/* Make a connection to the database */
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
				PQerrorMessage(conn));
		exit_nicely(conn);
	}

	/* Set always-secure search path, so malicious users can't take control. */
	res = PQexec(conn,
				 "SELECT pg_catalog.set_config('search_path', '', false)");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}

	/*
	 * Should PQclear PGresult whenever it is no longer needed to avoid memory
	 * leaks
	 */
	PQclear(res);

	/*
	 * Issue LISTEN command to enable notifications from the rule's NOTIFY.
	 */
	res = PQexec(conn, "LISTEN TBL2");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "LISTEN command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}
	PQclear(res);

	/* Quit after four notifies are received. */
	nnotifies = 0;
	while (nnotifies < 4)
	{
		/*
		 * Sleep until something happens on the connection.  We use select(2)
		 * to wait for input, but you could also use poll() or similar
		 * facilities.
		 */
		int			sock;
		fd_set		input_mask;

		sock = PQsocket(conn);

		if (sock < 0)
			break;				/* shouldn't happen */

		FD_ZERO(&input_mask);
		FD_SET(sock, &input_mask);

		if (select(sock + 1, &input_mask, NULL, NULL, NULL) < 0)
		{
			fprintf(stderr, "select() failed: %s\n", strerror(errno));
			exit_nicely(conn);
		}

		/* Now check for input */
		PQconsumeInput(conn);
		while ((notify = PQnotifies(conn)) != NULL)
		{
			fprintf(stderr,
					"ASYNC NOTIFY of '%s' received from backend PID %d\n",
					notify->relname, notify->be_pid);
			PQfreemem(notify);
			nnotifies++;
			PQconsumeInput(conn);
		}
	}

	fprintf(stderr, "Done.\n");

	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return 0;
}