#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql_file_name ;
typedef  int /*<<< orphan*/  log_file_name ;
struct TYPE_18__ {scalar_t__ verbose; } ;
struct TYPE_17__ {int /*<<< orphan*/  bindir; } ;
struct TYPE_13__ {int ndbs; TYPE_3__* dbs; } ;
struct TYPE_16__ {TYPE_1__ dbarr; } ;
struct TYPE_15__ {int /*<<< orphan*/  db_oid; int /*<<< orphan*/  db_name; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ DbInfo ;

/* Variables and functions */
 char* DB_DUMP_FILE_MASK ; 
 char* DB_DUMP_LOG_FILE_MASK ; 
 int /*<<< orphan*/  GLOBALS_DUMP_FILE ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_STATUS ; 
 int /*<<< orphan*/  UTILITY_LOG_FILE ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  appendShellString (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  cluster_conn_opts (TYPE_5__*) ; 
 int /*<<< orphan*/  end_progress_output () ; 
 int /*<<< orphan*/  exec_prog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 TYPE_7__ log_opts ; 
 TYPE_6__ new_cluster ; 
 TYPE_5__ old_cluster ; 
 int /*<<< orphan*/  parallel_exec_prog (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int reap_child (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

void
generate_old_dump(void)
{
	int			dbnum;

	prep_status("Creating dump of global objects");

	/* run new pg_dumpall binary for globals */
	exec_prog(UTILITY_LOG_FILE, NULL, true, true,
			  "\"%s/pg_dumpall\" %s --globals-only --quote-all-identifiers "
			  "--binary-upgrade %s -f %s",
			  new_cluster.bindir, cluster_conn_opts(&old_cluster),
			  log_opts.verbose ? "--verbose" : "",
			  GLOBALS_DUMP_FILE);
	check_ok();

	prep_status("Creating dump of database schemas\n");

	/* create per-db dump files */
	for (dbnum = 0; dbnum < old_cluster.dbarr.ndbs; dbnum++)
	{
		char		sql_file_name[MAXPGPATH],
					log_file_name[MAXPGPATH];
		DbInfo	   *old_db = &old_cluster.dbarr.dbs[dbnum];
		PQExpBufferData connstr,
					escaped_connstr;

		initPQExpBuffer(&connstr);
		appendPQExpBufferStr(&connstr, "dbname=");
		appendConnStrVal(&connstr, old_db->db_name);
		initPQExpBuffer(&escaped_connstr);
		appendShellString(&escaped_connstr, connstr.data);
		termPQExpBuffer(&connstr);

		pg_log(PG_STATUS, "%s", old_db->db_name);
		snprintf(sql_file_name, sizeof(sql_file_name), DB_DUMP_FILE_MASK, old_db->db_oid);
		snprintf(log_file_name, sizeof(log_file_name), DB_DUMP_LOG_FILE_MASK, old_db->db_oid);

		parallel_exec_prog(log_file_name, NULL,
						   "\"%s/pg_dump\" %s --schema-only --quote-all-identifiers "
						   "--binary-upgrade --format=custom %s --file=\"%s\" %s",
						   new_cluster.bindir, cluster_conn_opts(&old_cluster),
						   log_opts.verbose ? "--verbose" : "",
						   sql_file_name, escaped_connstr.data);

		termPQExpBuffer(&escaped_connstr);
	}

	/* reap all children */
	while (reap_child(true) == true)
		;

	end_progress_output();
	check_ok();
}