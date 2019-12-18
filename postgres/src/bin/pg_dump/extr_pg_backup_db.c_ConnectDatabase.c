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
typedef  scalar_t__ trivalue ;
typedef  int /*<<< orphan*/  passbuf ;
struct TYPE_4__ {char* savedPassword; scalar_t__ connection; scalar_t__ promptPassword; } ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 scalar_t__ CONNECTION_BAD ; 
 int /*<<< orphan*/  ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ ) ; 
 scalar_t__ PQconnectdbParams (char const**,char const**,int) ; 
 scalar_t__ PQconnectionNeedsPassword (scalar_t__) ; 
 scalar_t__ PQconnectionUsedPassword (scalar_t__) ; 
 char* PQdb (scalar_t__) ; 
 int /*<<< orphan*/  PQerrorMessage (scalar_t__) ; 
 int /*<<< orphan*/  PQfinish (scalar_t__) ; 
 int /*<<< orphan*/  PQpass (scalar_t__) ; 
 int /*<<< orphan*/  PQsetNoticeProcessor (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (scalar_t__) ; 
 scalar_t__ TRI_NO ; 
 scalar_t__ TRI_YES ; 
 int /*<<< orphan*/  _check_database_version (TYPE_1__*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  notice_processor ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 char* progname ; 
 int /*<<< orphan*/  set_archive_cancel_info (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 

void
ConnectDatabase(Archive *AHX,
				const char *dbname,
				const char *pghost,
				const char *pgport,
				const char *username,
				trivalue prompt_password)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	char	   *password;
	char		passbuf[100];
	bool		new_pass;

	if (AH->connection)
		fatal("already connected to a database");

	password = AH->savedPassword;

	if (prompt_password == TRI_YES && password == NULL)
	{
		simple_prompt("Password: ", passbuf, sizeof(passbuf), false);
		password = passbuf;
	}
	AH->promptPassword = prompt_password;

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
		values[2] = username;
		keywords[3] = "password";
		values[3] = password;
		keywords[4] = "dbname";
		values[4] = dbname;
		keywords[5] = "fallback_application_name";
		values[5] = progname;
		keywords[6] = NULL;
		values[6] = NULL;

		new_pass = false;
		AH->connection = PQconnectdbParams(keywords, values, true);

		if (!AH->connection)
			fatal("could not connect to database");

		if (PQstatus(AH->connection) == CONNECTION_BAD &&
			PQconnectionNeedsPassword(AH->connection) &&
			password == NULL &&
			prompt_password != TRI_NO)
		{
			PQfinish(AH->connection);
			simple_prompt("Password: ", passbuf, sizeof(passbuf), false);
			password = passbuf;
			new_pass = true;
		}
	} while (new_pass);

	/* check to see that the backend connection was successfully made */
	if (PQstatus(AH->connection) == CONNECTION_BAD)
		fatal("connection to database \"%s\" failed: %s",
			  PQdb(AH->connection) ? PQdb(AH->connection) : "",
			  PQerrorMessage(AH->connection));

	/* Start strict; later phases may override this. */
	PQclear(ExecuteSqlQueryForSingleRow((Archive *) AH,
										ALWAYS_SECURE_SEARCH_PATH_SQL));

	/*
	 * We want to remember connection's actual password, whether or not we got
	 * it by prompting.  So we don't just store the password variable.
	 */
	if (PQconnectionUsedPassword(AH->connection))
	{
		if (AH->savedPassword)
			free(AH->savedPassword);
		AH->savedPassword = pg_strdup(PQpass(AH->connection));
	}

	/* check for version mismatch */
	_check_database_version(AH);

	PQsetNoticeProcessor(AH->connection, notice_processor, NULL);

	/* arrange for SIGINT to issue a query cancel on this connection */
	set_archive_cancel_info(AH, AH->connection);
}