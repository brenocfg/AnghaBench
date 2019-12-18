#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  output_path ;
struct TYPE_10__ {int ndbs; TYPE_3__* dbs; } ;
struct TYPE_13__ {TYPE_1__ dbarr; } ;
struct TYPE_12__ {int /*<<< orphan*/  db_name; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ DbInfo ;
typedef  TYPE_4__ ClusterInfo ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_WARNING ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendPsqlMetaConnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/ * connectToServer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_priv (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  report_status (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

void
new_9_0_populate_pg_largeobject_metadata(ClusterInfo *cluster, bool check_mode)
{
	int			dbnum;
	FILE	   *script = NULL;
	bool		found = false;
	char		output_path[MAXPGPATH];

	prep_status("Checking for large objects");

	snprintf(output_path, sizeof(output_path), "pg_largeobject.sql");

	for (dbnum = 0; dbnum < cluster->dbarr.ndbs; dbnum++)
	{
		PGresult   *res;
		int			i_count;
		DbInfo	   *active_db = &cluster->dbarr.dbs[dbnum];
		PGconn	   *conn = connectToServer(cluster, active_db->db_name);

		/* find if there are any large objects */
		res = executeQueryOrDie(conn,
								"SELECT count(*) "
								"FROM	pg_catalog.pg_largeobject ");

		i_count = PQfnumber(res, "count");
		if (atoi(PQgetvalue(res, 0, i_count)) != 0)
		{
			found = true;
			if (!check_mode)
			{
				PQExpBufferData connectbuf;

				if (script == NULL && (script = fopen_priv(output_path, "w")) == NULL)
					pg_fatal("could not open file \"%s\": %s\n", output_path,
							 strerror(errno));

				initPQExpBuffer(&connectbuf);
				appendPsqlMetaConnect(&connectbuf, active_db->db_name);
				fputs(connectbuf.data, script);
				termPQExpBuffer(&connectbuf);

				fprintf(script,
						"SELECT pg_catalog.lo_create(t.loid)\n"
						"FROM (SELECT DISTINCT loid FROM pg_catalog.pg_largeobject) AS t;\n");
			}
		}

		PQclear(res);
		PQfinish(conn);
	}

	if (script)
		fclose(script);

	if (found)
	{
		report_status(PG_WARNING, "warning");
		if (check_mode)
			pg_log(PG_WARNING, "\n"
				   "Your installation contains large objects.  The new database has an\n"
				   "additional large object permission table.  After upgrading, you will be\n"
				   "given a command to populate the pg_largeobject_metadata table with\n"
				   "default permissions.\n\n");
		else
			pg_log(PG_WARNING, "\n"
				   "Your installation contains large objects.  The new database has an\n"
				   "additional large object permission table, so default permissions must be\n"
				   "defined for all large objects.  The file\n"
				   "    %s\n"
				   "when executed by psql by the database superuser will set the default\n"
				   "permissions.\n\n",
				   output_path);
	}
	else
		check_ok();
}