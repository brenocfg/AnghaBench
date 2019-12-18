#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql_file_name ;
typedef  int /*<<< orphan*/  log_file_name ;
struct TYPE_10__ {int /*<<< orphan*/  bindir; } ;
struct TYPE_7__ {int ndbs; TYPE_2__* dbs; } ;
struct TYPE_9__ {int /*<<< orphan*/  major_version; TYPE_1__ dbarr; } ;
struct TYPE_8__ {int /*<<< orphan*/  db_name; int /*<<< orphan*/  db_oid; } ;
typedef  TYPE_2__ DbInfo ;

/* Variables and functions */
 char* DB_DUMP_FILE_MASK ; 
 char* DB_DUMP_LOG_FILE_MASK ; 
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_STATUS ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  cluster_conn_opts (TYPE_4__*) ; 
 int /*<<< orphan*/  end_progress_output () ; 
 int /*<<< orphan*/  exec_prog (char*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  get_db_and_rel_infos (TYPE_4__*) ; 
 TYPE_4__ new_cluster ; 
 TYPE_3__ old_cluster ; 
 int /*<<< orphan*/  parallel_exec_prog (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int reap_child (int) ; 
 int /*<<< orphan*/  set_frozenxids (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
create_new_objects(void)
{
	int			dbnum;

	prep_status("Restoring database schemas in the new cluster\n");

	/*
	 * We cannot process the template1 database concurrently with others,
	 * because when it's transiently dropped, connection attempts would fail.
	 * So handle it in a separate non-parallelized pass.
	 */
	for (dbnum = 0; dbnum < old_cluster.dbarr.ndbs; dbnum++)
	{
		char		sql_file_name[MAXPGPATH],
					log_file_name[MAXPGPATH];
		DbInfo	   *old_db = &old_cluster.dbarr.dbs[dbnum];
		const char *create_opts;

		/* Process only template1 in this pass */
		if (strcmp(old_db->db_name, "template1") != 0)
			continue;

		pg_log(PG_STATUS, "%s", old_db->db_name);
		snprintf(sql_file_name, sizeof(sql_file_name), DB_DUMP_FILE_MASK, old_db->db_oid);
		snprintf(log_file_name, sizeof(log_file_name), DB_DUMP_LOG_FILE_MASK, old_db->db_oid);

		/*
		 * template1 and postgres databases will already exist in the target
		 * installation, so tell pg_restore to drop and recreate them;
		 * otherwise we would fail to propagate their database-level
		 * properties.
		 */
		create_opts = "--clean --create";

		exec_prog(log_file_name,
				  NULL,
				  true,
				  true,
				  "\"%s/pg_restore\" %s %s --exit-on-error --verbose "
				  "--dbname postgres \"%s\"",
				  new_cluster.bindir,
				  cluster_conn_opts(&new_cluster),
				  create_opts,
				  sql_file_name);

		break;					/* done once we've processed template1 */
	}

	for (dbnum = 0; dbnum < old_cluster.dbarr.ndbs; dbnum++)
	{
		char		sql_file_name[MAXPGPATH],
					log_file_name[MAXPGPATH];
		DbInfo	   *old_db = &old_cluster.dbarr.dbs[dbnum];
		const char *create_opts;

		/* Skip template1 in this pass */
		if (strcmp(old_db->db_name, "template1") == 0)
			continue;

		pg_log(PG_STATUS, "%s", old_db->db_name);
		snprintf(sql_file_name, sizeof(sql_file_name), DB_DUMP_FILE_MASK, old_db->db_oid);
		snprintf(log_file_name, sizeof(log_file_name), DB_DUMP_LOG_FILE_MASK, old_db->db_oid);

		/*
		 * template1 and postgres databases will already exist in the target
		 * installation, so tell pg_restore to drop and recreate them;
		 * otherwise we would fail to propagate their database-level
		 * properties.
		 */
		if (strcmp(old_db->db_name, "postgres") == 0)
			create_opts = "--clean --create";
		else
			create_opts = "--create";

		parallel_exec_prog(log_file_name,
						   NULL,
						   "\"%s/pg_restore\" %s %s --exit-on-error --verbose "
						   "--dbname template1 \"%s\"",
						   new_cluster.bindir,
						   cluster_conn_opts(&new_cluster),
						   create_opts,
						   sql_file_name);
	}

	/* reap all children */
	while (reap_child(true) == true)
		;

	end_progress_output();
	check_ok();

	/*
	 * We don't have minmxids for databases or relations in pre-9.3 clusters,
	 * so set those after we have restored the schema.
	 */
	if (GET_MAJOR_VERSION(old_cluster.major_version) < 903)
		set_frozenxids(true);

	/* update new_cluster info now that we have objects in the databases */
	get_db_and_rel_infos(&new_cluster);
}