#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  old_path ;
typedef  int /*<<< orphan*/  new_path ;
struct TYPE_2__ {char* pgdata; } ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  check_ok () ; 
 TYPE_1__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,char*) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ pg_mv_file (char*,char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void
disable_old_cluster(void)
{
	char		old_path[MAXPGPATH],
				new_path[MAXPGPATH];

	/* rename pg_control so old server cannot be accidentally started */
	prep_status("Adding \".old\" suffix to old global/pg_control");

	snprintf(old_path, sizeof(old_path), "%s/global/pg_control", old_cluster.pgdata);
	snprintf(new_path, sizeof(new_path), "%s/global/pg_control.old", old_cluster.pgdata);
	if (pg_mv_file(old_path, new_path) != 0)
		pg_fatal("Unable to rename %s to %s.\n", old_path, new_path);
	check_ok();

	pg_log(PG_REPORT, "\n"
		   "If you want to start the old cluster, you will need to remove\n"
		   "the \".old\" suffix from %s/global/pg_control.old.\n"
		   "Because \"link\" mode was used, the old cluster cannot be safely\n"
		   "started once the new cluster has been started.\n\n", old_cluster.pgdata);
}