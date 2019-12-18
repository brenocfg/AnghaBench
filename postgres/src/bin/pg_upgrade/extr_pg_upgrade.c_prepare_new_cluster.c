#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ verbose; } ;
struct TYPE_4__ {int /*<<< orphan*/  bindir; } ;

/* Variables and functions */
 int /*<<< orphan*/  UTILITY_LOG_FILE ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  cluster_conn_opts (TYPE_1__*) ; 
 int /*<<< orphan*/  exec_prog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ log_opts ; 
 TYPE_1__ new_cluster ; 
 int /*<<< orphan*/  prep_status (char*) ; 

__attribute__((used)) static void
prepare_new_cluster(void)
{
	/*
	 * It would make more sense to freeze after loading the schema, but that
	 * would cause us to lose the frozenxids restored by the load. We use
	 * --analyze so autovacuum doesn't update statistics later
	 */
	prep_status("Analyzing all rows in the new cluster");
	exec_prog(UTILITY_LOG_FILE, NULL, true, true,
			  "\"%s/vacuumdb\" %s --all --analyze %s",
			  new_cluster.bindir, cluster_conn_opts(&new_cluster),
			  log_opts.verbose ? "--verbose" : "");
	check_ok();

	/*
	 * We do freeze after analyze so pg_statistic is also frozen. template0 is
	 * not frozen here, but data rows were frozen by initdb, and we set its
	 * datfrozenxid, relfrozenxids, and relminmxid later to match the new xid
	 * counter later.
	 */
	prep_status("Freezing all rows in the new cluster");
	exec_prog(UTILITY_LOG_FILE, NULL, true, true,
			  "\"%s/vacuumdb\" %s --all --freeze %s",
			  new_cluster.bindir, cluster_conn_opts(&new_cluster),
			  log_opts.verbose ? "--verbose" : "");
	check_ok();
}