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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 int PARAMS_ARRAY_SIZE ; 
 int /*<<< orphan*/ * PQconnectdbParams (char const**,char const**,int) ; 
 scalar_t__ PQconnectionNeedsPassword (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 char* dbName ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* login ; 
 char* pghost ; 
 char* pgport ; 
 char* progname ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static PGconn *
doConnect(void)
{
	PGconn	   *conn;
	bool		new_pass;
	static bool have_password = false;
	static char password[100];

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
		values[0] = pghost;
		keywords[1] = "port";
		values[1] = pgport;
		keywords[2] = "user";
		values[2] = login;
		keywords[3] = "password";
		values[3] = have_password ? password : NULL;
		keywords[4] = "dbname";
		values[4] = dbName;
		keywords[5] = "fallback_application_name";
		values[5] = progname;
		keywords[6] = NULL;
		values[6] = NULL;

		new_pass = false;

		conn = PQconnectdbParams(keywords, values, true);

		if (!conn)
		{
			fprintf(stderr, "connection to database \"%s\" failed\n",
					dbName);
			return NULL;
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
		fprintf(stderr, "connection to database \"%s\" failed:\n%s",
				dbName, PQerrorMessage(conn));
		PQfinish(conn);
		return NULL;
	}

	return conn;
}