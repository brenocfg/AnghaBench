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
struct options {char* hostname; char* port; char* username; char* dbname; char* progname; } ;
typedef  int /*<<< orphan*/  password ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 scalar_t__ CONNECTION_BAD ; 
 int PARAMS_ARRAY_SIZE ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQconnectdbParams (char const**,char const**,int) ; 
 scalar_t__ PQconnectionNeedsPassword (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,...) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 

PGconn *
sql_conn(struct options *my_opts)
{
	PGconn	   *conn;
	bool		have_password = false;
	char		password[100];
	bool		new_pass;
	PGresult   *res;

	/*
	 * Start the connection.  Loop until we have a password if requested by
	 * backend.
	 */
	do
	{
#define PARAMS_ARRAY_SIZE	7

		const char *keywords[PARAMS_ARRAY_SIZE];
		const char *values[PARAMS_ARRAY_SIZE];

		keywords[0] = "host";
		values[0] = my_opts->hostname;
		keywords[1] = "port";
		values[1] = my_opts->port;
		keywords[2] = "user";
		values[2] = my_opts->username;
		keywords[3] = "password";
		values[3] = have_password ? password : NULL;
		keywords[4] = "dbname";
		values[4] = my_opts->dbname;
		keywords[5] = "fallback_application_name";
		values[5] = my_opts->progname;
		keywords[6] = NULL;
		values[6] = NULL;

		new_pass = false;
		conn = PQconnectdbParams(keywords, values, true);

		if (!conn)
		{
			pg_log_error("could not connect to database %s",
						 my_opts->dbname);
			exit(1);
		}

		if (PQstatus(conn) == CONNECTION_BAD &&
			PQconnectionNeedsPassword(conn) &&
			!have_password)
		{
			PQfinish(conn);
			simple_prompt("Password: ", password, sizeof(password), false);
			have_password = true;
			new_pass = true;
		}
	} while (new_pass);

	/* check to see that the backend connection was successfully made */
	if (PQstatus(conn) == CONNECTION_BAD)
	{
		pg_log_error("could not connect to database %s: %s",
					 my_opts->dbname, PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}

	res = PQexec(conn, ALWAYS_SECURE_SEARCH_PATH_SQL);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		pg_log_error("could not clear search_path: %s",
					 PQerrorMessage(conn));
		PQclear(res);
		PQfinish(conn);
		exit(-1);
	}
	PQclear(res);

	/* return the conn if good */
	return conn;
}