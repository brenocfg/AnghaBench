#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  OPF ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtId (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ if_exists ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  role_catalog ; 
 int server_version ; 

__attribute__((used)) static void
dropRoles(PGconn *conn)
{
	PQExpBuffer buf = createPQExpBuffer();
	PGresult   *res;
	int			i_rolname;
	int			i;

	if (server_version >= 90600)
		printfPQExpBuffer(buf,
						  "SELECT rolname "
						  "FROM %s "
						  "WHERE rolname !~ '^pg_' "
						  "ORDER BY 1", role_catalog);
	else if (server_version >= 80100)
		printfPQExpBuffer(buf,
						  "SELECT rolname "
						  "FROM %s "
						  "ORDER BY 1", role_catalog);
	else
		printfPQExpBuffer(buf,
						  "SELECT usename as rolname "
						  "FROM pg_shadow "
						  "UNION "
						  "SELECT groname as rolname "
						  "FROM pg_group "
						  "ORDER BY 1");

	res = executeQuery(conn, buf->data);

	i_rolname = PQfnumber(res, "rolname");

	if (PQntuples(res) > 0)
		fprintf(OPF, "--\n-- Drop roles\n--\n\n");

	for (i = 0; i < PQntuples(res); i++)
	{
		const char *rolename;

		rolename = PQgetvalue(res, i, i_rolname);

		fprintf(OPF, "DROP ROLE %s%s;\n",
				if_exists ? "IF EXISTS " : "",
				fmtId(rolename));
	}

	PQclear(res);
	destroyPQExpBuffer(buf);

	fprintf(OPF, "\n\n");
}