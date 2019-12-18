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
typedef  int /*<<< orphan*/  password ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 scalar_t__ CONNECTION_BAD ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQconnectdbParams (char const**,char const**,int) ; 
 scalar_t__ PQconnectionNeedsPassword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int TRI_NO ; 
 int TRI_YES ; 
 int /*<<< orphan*/  executeQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,...) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 

PGconn *
connectDatabase(const char *dbname, const char *pghost,
				const char *pgport, const char *pguser,
				enum trivalue prompt_password, const char *progname,
				bool echo, bool fail_ok, bool allow_password_reuse)
{
	PGconn	   *conn;
	bool		new_pass;
	static bool have_password = false;
	static char password[100];

	if (!allow_password_reuse)
		have_password = false;

	if (!have_password && prompt_password == TRI_YES)
	{
		simple_prompt("Password: ", password, sizeof(password), false);
		have_password = true;
	}

	/*
	 * Start the connection.  Loop until we have a password if requested by
	 * backend.
	 */
	do
	{
		const char *keywords[7];
		const char *values[7];

		keywords[0] = "host";
		values[0] = pghost;
		keywords[1] = "port";
		values[1] = pgport;
		keywords[2] = "user";
		values[2] = pguser;
		keywords[3] = "password";
		values[3] = have_password ? password : NULL;
		keywords[4] = "dbname";
		values[4] = dbname;
		keywords[5] = "fallback_application_name";
		values[5] = progname;
		keywords[6] = NULL;
		values[6] = NULL;

		new_pass = false;
		conn = PQconnectdbParams(keywords, values, true);

		if (!conn)
		{
			pg_log_error("could not connect to database %s: out of memory",
						 dbname);
			exit(1);
		}

		/*
		 * No luck?  Trying asking (again) for a password.
		 */
		if (PQstatus(conn) == CONNECTION_BAD &&
			PQconnectionNeedsPassword(conn) &&
			prompt_password != TRI_NO)
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
		if (fail_ok)
		{
			PQfinish(conn);
			return NULL;
		}
		pg_log_error("could not connect to database %s: %s",
					 dbname, PQerrorMessage(conn));
		exit(1);
	}

	PQclear(executeQuery(conn, ALWAYS_SECURE_SEARCH_PATH_SQL, echo));

	return conn;
}