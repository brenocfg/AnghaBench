#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  chkpnt_nxtoid; } ;
struct TYPE_10__ {int /*<<< orphan*/  pgdata; int /*<<< orphan*/  bindir; TYPE_1__ controldata; int /*<<< orphan*/  dbarr; } ;
struct TYPE_9__ {scalar_t__ transfer_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetDataDirectoryCreatePerm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_MODE_MASK_OWNER ; 
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 scalar_t__ TRANSFER_MODE_LINK ; 
 int /*<<< orphan*/  UTILITY_LOG_FILE ; 
 int /*<<< orphan*/  adjust_data_dir (TYPE_3__*) ; 
 int /*<<< orphan*/  check_and_dump_old_cluster (int) ; 
 int /*<<< orphan*/  check_cluster_compatibility (int) ; 
 int /*<<< orphan*/  check_cluster_versions () ; 
 int /*<<< orphan*/  check_new_cluster () ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  copy_xact_xlog_xid () ; 
 int /*<<< orphan*/  create_new_objects () ; 
 int /*<<< orphan*/  create_script_for_cluster_analyze (char**) ; 
 int /*<<< orphan*/  create_script_for_old_cluster_deletion (char**) ; 
 int /*<<< orphan*/  disable_old_cluster () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exec_prog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  get_restricted_token () ; 
 int /*<<< orphan*/  get_sock_dir (TYPE_3__*,int) ; 
 int /*<<< orphan*/  issue_warnings_and_set_wal_level () ; 
 TYPE_3__ new_cluster ; 
 TYPE_3__ old_cluster ; 
 int /*<<< orphan*/  output_check_banner (int) ; 
 int /*<<< orphan*/  output_completion_banner (char*,char*) ; 
 int /*<<< orphan*/  parseCommandLine (int,char**) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_logging_init (char*) ; 
 int /*<<< orphan*/  pg_mode_mask ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  prepare_new_cluster () ; 
 int /*<<< orphan*/  prepare_new_globals () ; 
 int /*<<< orphan*/  report_clusters_compatible () ; 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup (char*,int*) ; 
 int /*<<< orphan*/  start_postmaster (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stop_postmaster (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_all_new_tablespaces (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 
 TYPE_2__ user_opts ; 

int
main(int argc, char **argv)
{
	char	   *analyze_script_file_name = NULL;
	char	   *deletion_script_file_name = NULL;
	bool		live_check = false;

	pg_logging_init(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pg_upgrade"));

	/* Set default restrictive mask until new cluster permissions are read */
	umask(PG_MODE_MASK_OWNER);

	parseCommandLine(argc, argv);

	get_restricted_token();

	adjust_data_dir(&old_cluster);
	adjust_data_dir(&new_cluster);

	setup(argv[0], &live_check);

	output_check_banner(live_check);

	check_cluster_versions();

	get_sock_dir(&old_cluster, live_check);
	get_sock_dir(&new_cluster, false);

	check_cluster_compatibility(live_check);

	/* Set mask based on PGDATA permissions */
	if (!GetDataDirectoryCreatePerm(new_cluster.pgdata))
		pg_fatal("could not read permissions of directory \"%s\": %s\n",
				 new_cluster.pgdata, strerror(errno));

	umask(pg_mode_mask);

	check_and_dump_old_cluster(live_check);


	/* -- NEW -- */
	start_postmaster(&new_cluster, true);

	check_new_cluster();
	report_clusters_compatible();

	pg_log(PG_REPORT,
		   "\n"
		   "Performing Upgrade\n"
		   "------------------\n");

	prepare_new_cluster();

	stop_postmaster(false);

	/*
	 * Destructive Changes to New Cluster
	 */

	copy_xact_xlog_xid();

	/* New now using xids of the old system */

	/* -- NEW -- */
	start_postmaster(&new_cluster, true);

	prepare_new_globals();

	create_new_objects();

	stop_postmaster(false);

	/*
	 * Most failures happen in create_new_objects(), which has completed at
	 * this point.  We do this here because it is just before linking, which
	 * will link the old and new cluster data files, preventing the old
	 * cluster from being safely started once the new cluster is started.
	 */
	if (user_opts.transfer_mode == TRANSFER_MODE_LINK)
		disable_old_cluster();

	transfer_all_new_tablespaces(&old_cluster.dbarr, &new_cluster.dbarr,
								 old_cluster.pgdata, new_cluster.pgdata);

	/*
	 * Assuming OIDs are only used in system tables, there is no need to
	 * restore the OID counter because we have not transferred any OIDs from
	 * the old system, but we do it anyway just in case.  We do it late here
	 * because there is no need to have the schema load use new oids.
	 */
	prep_status("Setting next OID for new cluster");
	exec_prog(UTILITY_LOG_FILE, NULL, true, true,
			  "\"%s/pg_resetwal\" -o %u \"%s\"",
			  new_cluster.bindir, old_cluster.controldata.chkpnt_nxtoid,
			  new_cluster.pgdata);
	check_ok();

	prep_status("Sync data directory to disk");
	exec_prog(UTILITY_LOG_FILE, NULL, true, true,
			  "\"%s/initdb\" --sync-only \"%s\"", new_cluster.bindir,
			  new_cluster.pgdata);
	check_ok();

	create_script_for_cluster_analyze(&analyze_script_file_name);
	create_script_for_old_cluster_deletion(&deletion_script_file_name);

	issue_warnings_and_set_wal_level();

	pg_log(PG_REPORT,
		   "\n"
		   "Upgrade Complete\n"
		   "----------------\n");

	output_completion_banner(analyze_script_file_name,
							 deletion_script_file_name);

	pg_free(analyze_script_file_name);
	pg_free(deletion_script_file_name);

	cleanup();

	return 0;
}