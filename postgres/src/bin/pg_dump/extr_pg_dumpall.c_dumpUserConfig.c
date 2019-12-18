#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  OPF ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  makeAlterConfigCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  role_catalog ; 
 int server_version ; 

__attribute__((used)) static void
dumpUserConfig(PGconn *conn, const char *username)
{
	PQExpBuffer buf = createPQExpBuffer();
	int			count = 1;
	bool		first = true;

	for (;;)
	{
		PGresult   *res;

		if (server_version >= 90000)
			printfPQExpBuffer(buf, "SELECT setconfig[%d] FROM pg_db_role_setting WHERE "
							  "setdatabase = 0 AND setrole = "
							  "(SELECT oid FROM %s WHERE rolname = ", count, role_catalog);
		else if (server_version >= 80100)
			printfPQExpBuffer(buf, "SELECT rolconfig[%d] FROM %s WHERE rolname = ", count, role_catalog);
		else
			printfPQExpBuffer(buf, "SELECT useconfig[%d] FROM pg_shadow WHERE usename = ", count);
		appendStringLiteralConn(buf, username, conn);
		if (server_version >= 90000)
			appendPQExpBufferChar(buf, ')');

		res = executeQuery(conn, buf->data);
		if (PQntuples(res) == 1 &&
			!PQgetisnull(res, 0, 0))
		{
			/* comment at section start, only if needed */
			if (first)
			{
				fprintf(OPF, "--\n-- User Configurations\n--\n\n");
				first = false;
			}

			fprintf(OPF, "--\n-- User Config \"%s\"\n--\n\n", username);
			resetPQExpBuffer(buf);
			makeAlterConfigCommand(conn, PQgetvalue(res, 0, 0),
								   "ROLE", username, NULL, NULL,
								   buf);
			fprintf(OPF, "%s", buf->data);
			PQclear(res);
			count++;
		}
		else
		{
			PQclear(res);
			break;
		}
	}

	destroyPQExpBuffer(buf);
}