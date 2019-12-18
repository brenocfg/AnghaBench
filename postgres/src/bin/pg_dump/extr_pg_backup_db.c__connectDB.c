#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  passbuf ;
struct TYPE_10__ {char* savedPassword; scalar_t__ promptPassword; int /*<<< orphan*/  connection; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 int /*<<< orphan*/ * PQconnectdbParams (char const**,char const**,int) ; 
 int /*<<< orphan*/  PQconnectionNeedsPassword (int /*<<< orphan*/ *) ; 
 scalar_t__ PQconnectionUsedPassword (int /*<<< orphan*/ *) ; 
 char* PQdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 char* PQhost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQpass (int /*<<< orphan*/ *) ; 
 char* PQport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsetNoticeProcessor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 char* PQuser (int /*<<< orphan*/ ) ; 
 scalar_t__ TRI_NO ; 
 scalar_t__ TRI_YES ; 
 int /*<<< orphan*/  _check_database_version (TYPE_2__*) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  notice_processor ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*,char const*) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 char* progname ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static PGconn *
_connectDB(ArchiveHandle *AH, const char *reqdb, const char *requser)
{
	PQExpBufferData connstr;
	PGconn	   *newConn;
	const char *newdb;
	const char *newuser;
	char	   *password;
	char		passbuf[100];
	bool		new_pass;

	if (!reqdb)
		newdb = PQdb(AH->connection);
	else
		newdb = reqdb;

	if (!requser || strlen(requser) == 0)
		newuser = PQuser(AH->connection);
	else
		newuser = requser;

	pg_log_info("connecting to database \"%s\" as user \"%s\"",
				newdb, newuser);

	password = AH->savedPassword;

	if (AH->promptPassword == TRI_YES && password == NULL)
	{
		simple_prompt("Password: ", passbuf, sizeof(passbuf), false);
		password = passbuf;
	}

	initPQExpBuffer(&connstr);
	appendPQExpBufferStr(&connstr, "dbname=");
	appendConnStrVal(&connstr, newdb);

	do
	{
		const char *keywords[7];
		const char *values[7];

		keywords[0] = "host";
		values[0] = PQhost(AH->connection);
		keywords[1] = "port";
		values[1] = PQport(AH->connection);
		keywords[2] = "user";
		values[2] = newuser;
		keywords[3] = "password";
		values[3] = password;
		keywords[4] = "dbname";
		values[4] = connstr.data;
		keywords[5] = "fallback_application_name";
		values[5] = progname;
		keywords[6] = NULL;
		values[6] = NULL;

		new_pass = false;
		newConn = PQconnectdbParams(keywords, values, true);

		if (!newConn)
			fatal("could not reconnect to database");

		if (PQstatus(newConn) == CONNECTION_BAD)
		{
			if (!PQconnectionNeedsPassword(newConn))
				fatal("could not reconnect to database: %s",
					  PQerrorMessage(newConn));
			PQfinish(newConn);

			if (password)
				fprintf(stderr, "Password incorrect\n");

			fprintf(stderr, "Connecting to %s as %s\n",
					newdb, newuser);

			if (AH->promptPassword != TRI_NO)
			{
				simple_prompt("Password: ", passbuf, sizeof(passbuf), false);
				password = passbuf;
			}
			else
				fatal("connection needs password");

			new_pass = true;
		}
	} while (new_pass);

	/*
	 * We want to remember connection's actual password, whether or not we got
	 * it by prompting.  So we don't just store the password variable.
	 */
	if (PQconnectionUsedPassword(newConn))
	{
		if (AH->savedPassword)
			free(AH->savedPassword);
		AH->savedPassword = pg_strdup(PQpass(newConn));
	}

	termPQExpBuffer(&connstr);

	/* check for version mismatch */
	_check_database_version(AH);

	PQsetNoticeProcessor(newConn, notice_processor, NULL);

	return newConn;
}