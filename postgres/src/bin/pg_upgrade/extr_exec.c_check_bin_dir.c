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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  bindir; int /*<<< orphan*/  bin_version; } ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_FATAL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_bin_version (TYPE_1__*) ; 
 TYPE_1__ new_cluster ; 
 int /*<<< orphan*/  report_status (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_exec (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
check_bin_dir(ClusterInfo *cluster)
{
	struct stat statBuf;

	/* check bindir */
	if (stat(cluster->bindir, &statBuf) != 0)
		report_status(PG_FATAL, "check for \"%s\" failed: %s\n",
					  cluster->bindir, strerror(errno));
	else if (!S_ISDIR(statBuf.st_mode))
		report_status(PG_FATAL, "\"%s\" is not a directory\n",
					  cluster->bindir);

	validate_exec(cluster->bindir, "postgres");
	validate_exec(cluster->bindir, "pg_controldata");
	validate_exec(cluster->bindir, "pg_ctl");

	/*
	 * Fetch the binary version after checking for the existence of pg_ctl.
	 * This way we report a useful error if the pg_ctl binary used for version
	 * fetching is missing/broken.
	 */
	get_bin_version(cluster);

	/* pg_resetxlog has been renamed to pg_resetwal in version 10 */
	if (GET_MAJOR_VERSION(cluster->bin_version) < 1000)
		validate_exec(cluster->bindir, "pg_resetxlog");
	else
		validate_exec(cluster->bindir, "pg_resetwal");

	if (cluster == &new_cluster)
	{
		/*
		 * These binaries are only needed for the target version. pg_dump and
		 * pg_dumpall are used to dump the old cluster, but must be of the
		 * target version.
		 */
		validate_exec(cluster->bindir, "initdb");
		validate_exec(cluster->bindir, "pg_dump");
		validate_exec(cluster->bindir, "pg_dumpall");
		validate_exec(cluster->bindir, "pg_restore");
		validate_exec(cluster->bindir, "psql");
		validate_exec(cluster->bindir, "vacuumdb");
	}
}