#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int remoteVersion; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetConnection (TYPE_2__*) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  makeAlterConfigCommand (int /*<<< orphan*/ *,char const*,char*,char const*,char*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,int,...) ; 

__attribute__((used)) static void
dumpDatabaseConfig(Archive *AH, PQExpBuffer outbuf,
				   const char *dbname, Oid dboid)
{
	PGconn	   *conn = GetConnection(AH);
	PQExpBuffer buf = createPQExpBuffer();
	PGresult   *res;
	int			count = 1;

	/*
	 * First collect database-specific options.  Pre-8.4 server versions lack
	 * unnest(), so we do this the hard way by querying once per subscript.
	 */
	for (;;)
	{
		if (AH->remoteVersion >= 90000)
			printfPQExpBuffer(buf, "SELECT setconfig[%d] FROM pg_db_role_setting "
							  "WHERE setrole = 0 AND setdatabase = '%u'::oid",
							  count, dboid);
		else
			printfPQExpBuffer(buf, "SELECT datconfig[%d] FROM pg_database WHERE oid = '%u'::oid", count, dboid);

		res = ExecuteSqlQuery(AH, buf->data, PGRES_TUPLES_OK);

		if (PQntuples(res) == 1 &&
			!PQgetisnull(res, 0, 0))
		{
			makeAlterConfigCommand(conn, PQgetvalue(res, 0, 0),
								   "DATABASE", dbname, NULL, NULL,
								   outbuf);
			PQclear(res);
			count++;
		}
		else
		{
			PQclear(res);
			break;
		}
	}

	/* Now look for role-and-database-specific options */
	if (AH->remoteVersion >= 90000)
	{
		/* Here we can assume we have unnest() */
		printfPQExpBuffer(buf, "SELECT rolname, unnest(setconfig) "
						  "FROM pg_db_role_setting s, pg_roles r "
						  "WHERE setrole = r.oid AND setdatabase = '%u'::oid",
						  dboid);

		res = ExecuteSqlQuery(AH, buf->data, PGRES_TUPLES_OK);

		if (PQntuples(res) > 0)
		{
			int			i;

			for (i = 0; i < PQntuples(res); i++)
				makeAlterConfigCommand(conn, PQgetvalue(res, i, 1),
									   "ROLE", PQgetvalue(res, i, 0),
									   "DATABASE", dbname,
									   outbuf);
		}

		PQclear(res);
	}

	destroyPQExpBuffer(buf);
}