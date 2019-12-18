#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pw2 ;
typedef  int /*<<< orphan*/  pw1 ;
typedef  int /*<<< orphan*/  backslashResult ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  OT_SQLID ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQencryptPasswordConn (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 char* PQuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtId (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static backslashResult
exec_command_password(PsqlScanState scan_state, bool active_branch)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *opt0 = psql_scan_slash_option(scan_state,
												  OT_SQLID, NULL, true);
		char		pw1[100];
		char		pw2[100];

		simple_prompt("Enter new password: ", pw1, sizeof(pw1), false);
		simple_prompt("Enter it again: ", pw2, sizeof(pw2), false);

		if (strcmp(pw1, pw2) != 0)
		{
			pg_log_error("Passwords didn't match.");
			success = false;
		}
		else
		{
			char	   *user;
			char	   *encrypted_password;

			if (opt0)
				user = opt0;
			else
				user = PQuser(pset.db);

			encrypted_password = PQencryptPasswordConn(pset.db, pw1, user, NULL);

			if (!encrypted_password)
			{
				pg_log_info("%s", PQerrorMessage(pset.db));
				success = false;
			}
			else
			{
				PQExpBufferData buf;
				PGresult   *res;

				initPQExpBuffer(&buf);
				printfPQExpBuffer(&buf, "ALTER USER %s PASSWORD ",
								  fmtId(user));
				appendStringLiteralConn(&buf, encrypted_password, pset.db);
				res = PSQLexec(buf.data);
				termPQExpBuffer(&buf);
				if (!res)
					success = false;
				else
					PQclear(res);
				PQfreemem(encrypted_password);
			}
		}

		if (opt0)
			free(opt0);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}