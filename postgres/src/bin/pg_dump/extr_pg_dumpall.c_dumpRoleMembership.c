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
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fmtId (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  role_catalog ; 

__attribute__((used)) static void
dumpRoleMembership(PGconn *conn)
{
	PQExpBuffer buf = createPQExpBuffer();
	PGresult   *res;
	int			i;

	printfPQExpBuffer(buf, "SELECT ur.rolname AS roleid, "
					  "um.rolname AS member, "
					  "a.admin_option, "
					  "ug.rolname AS grantor "
					  "FROM pg_auth_members a "
					  "LEFT JOIN %s ur on ur.oid = a.roleid "
					  "LEFT JOIN %s um on um.oid = a.member "
					  "LEFT JOIN %s ug on ug.oid = a.grantor "
					  "WHERE NOT (ur.rolname ~ '^pg_' AND um.rolname ~ '^pg_')"
					  "ORDER BY 1,2,3", role_catalog, role_catalog, role_catalog);
	res = executeQuery(conn, buf->data);

	if (PQntuples(res) > 0)
		fprintf(OPF, "--\n-- Role memberships\n--\n\n");

	for (i = 0; i < PQntuples(res); i++)
	{
		char	   *roleid = PQgetvalue(res, i, 0);
		char	   *member = PQgetvalue(res, i, 1);
		char	   *option = PQgetvalue(res, i, 2);

		fprintf(OPF, "GRANT %s", fmtId(roleid));
		fprintf(OPF, " TO %s", fmtId(member));
		if (*option == 't')
			fprintf(OPF, " WITH ADMIN OPTION");

		/*
		 * We don't track the grantor very carefully in the backend, so cope
		 * with the possibility that it has been dropped.
		 */
		if (!PQgetisnull(res, i, 3))
		{
			char	   *grantor = PQgetvalue(res, i, 3);

			fprintf(OPF, " GRANTED BY %s", fmtId(grantor));
		}
		fprintf(OPF, ";\n");
	}

	PQclear(res);
	destroyPQExpBuffer(buf);

	fprintf(OPF, "\n\n");
}