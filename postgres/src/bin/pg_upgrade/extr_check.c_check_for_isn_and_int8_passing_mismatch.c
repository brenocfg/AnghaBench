#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  output_path ;
struct TYPE_11__ {scalar_t__ float8_pass_by_value; } ;
struct TYPE_16__ {TYPE_2__ controldata; } ;
struct TYPE_10__ {scalar_t__ float8_pass_by_value; } ;
struct TYPE_15__ {TYPE_1__ controldata; } ;
struct TYPE_12__ {int ndbs; TYPE_4__* dbs; } ;
struct TYPE_14__ {TYPE_3__ dbarr; } ;
struct TYPE_13__ {char* db_name; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_4__ DbInfo ;
typedef  TYPE_5__ ClusterInfo ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/ * connectToServer (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_priv (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 TYPE_7__ new_cluster ; 
 TYPE_6__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,...) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_for_isn_and_int8_passing_mismatch(ClusterInfo *cluster)
{
	int			dbnum;
	FILE	   *script = NULL;
	bool		found = false;
	char		output_path[MAXPGPATH];

	prep_status("Checking for contrib/isn with bigint-passing mismatch");

	if (old_cluster.controldata.float8_pass_by_value ==
		new_cluster.controldata.float8_pass_by_value)
	{
		/* no mismatch */
		check_ok();
		return;
	}

	snprintf(output_path, sizeof(output_path),
			 "contrib_isn_and_int8_pass_by_value.txt");

	for (dbnum = 0; dbnum < cluster->dbarr.ndbs; dbnum++)
	{
		PGresult   *res;
		bool		db_used = false;
		int			ntups;
		int			rowno;
		int			i_nspname,
					i_proname;
		DbInfo	   *active_db = &cluster->dbarr.dbs[dbnum];
		PGconn	   *conn = connectToServer(cluster, active_db->db_name);

		/* Find any functions coming from contrib/isn */
		res = executeQueryOrDie(conn,
								"SELECT n.nspname, p.proname "
								"FROM	pg_catalog.pg_proc p, "
								"		pg_catalog.pg_namespace n "
								"WHERE	p.pronamespace = n.oid AND "
								"		p.probin = '$libdir/isn'");

		ntups = PQntuples(res);
		i_nspname = PQfnumber(res, "nspname");
		i_proname = PQfnumber(res, "proname");
		for (rowno = 0; rowno < ntups; rowno++)
		{
			found = true;
			if (script == NULL && (script = fopen_priv(output_path, "w")) == NULL)
				pg_fatal("could not open file \"%s\": %s\n",
						 output_path, strerror(errno));
			if (!db_used)
			{
				fprintf(script, "In database: %s\n", active_db->db_name);
				db_used = true;
			}
			fprintf(script, "  %s.%s\n",
					PQgetvalue(res, rowno, i_nspname),
					PQgetvalue(res, rowno, i_proname));
		}

		PQclear(res);

		PQfinish(conn);
	}

	if (script)
		fclose(script);

	if (found)
	{
		pg_log(PG_REPORT, "fatal\n");
		pg_fatal("Your installation contains \"contrib/isn\" functions which rely on the\n"
				 "bigint data type.  Your old and new clusters pass bigint values\n"
				 "differently so this cluster cannot currently be upgraded.  You can\n"
				 "manually upgrade databases that use \"contrib/isn\" facilities and remove\n"
				 "\"contrib/isn\" from the old cluster and restart the upgrade.  A list of\n"
				 "the problem functions is in the file:\n"
				 "    %s\n\n", output_path);
	}
	else
		check_ok();
}