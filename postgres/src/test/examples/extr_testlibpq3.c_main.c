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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  binaryIntVal ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQconnectdb (char const*) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PQexecParams (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,char const**,int*,int*,int) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_nicely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_binary_results (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	const char *conninfo;
	PGconn	   *conn;
	PGresult   *res;
	const char *paramValues[1];
	int			paramLengths[1];
	int			paramFormats[1];
	uint32_t	binaryIntVal;

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
	res = PQexec(conn, "SET search_path = testlibpq3");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}
	PQclear(res);

	/*
	 * The point of this program is to illustrate use of PQexecParams() with
	 * out-of-line parameters, as well as binary transmission of data.
	 *
	 * This first example transmits the parameters as text, but receives the
	 * results in binary format.  By using out-of-line parameters we can avoid
	 * a lot of tedious mucking about with quoting and escaping, even though
	 * the data is text.  Notice how we don't have to do anything special with
	 * the quote mark in the parameter value.
	 */

	/* Here is our out-of-line parameter value */
	paramValues[0] = "joe's place";

	res = PQexecParams(conn,
					   "SELECT * FROM test1 WHERE t = $1",
					   1,		/* one param */
					   NULL,	/* let the backend deduce param type */
					   paramValues,
					   NULL,	/* don't need param lengths since text */
					   NULL,	/* default to all text params */
					   1);		/* ask for binary results */

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}

	show_binary_results(res);

	PQclear(res);

	/*
	 * In this second example we transmit an integer parameter in binary form,
	 * and again retrieve the results in binary form.
	 *
	 * Although we tell PQexecParams we are letting the backend deduce
	 * parameter type, we really force the decision by casting the parameter
	 * symbol in the query text.  This is a good safety measure when sending
	 * binary parameters.
	 */

	/* Convert integer value "2" to network byte order */
	binaryIntVal = htonl((uint32_t) 2);

	/* Set up parameter arrays for PQexecParams */
	paramValues[0] = (char *) &binaryIntVal;
	paramLengths[0] = sizeof(binaryIntVal);
	paramFormats[0] = 1;		/* binary */

	res = PQexecParams(conn,
					   "SELECT * FROM test1 WHERE i = $1::int4",
					   1,		/* one param */
					   NULL,	/* let the backend deduce param type */
					   paramValues,
					   paramLengths,
					   paramFormats,
					   1);		/* ask for binary results */

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}

	show_binary_results(res);

	PQclear(res);

	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return 0;
}