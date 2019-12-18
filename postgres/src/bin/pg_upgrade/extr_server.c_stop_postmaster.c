#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* running_cluster; } ;
struct TYPE_5__ {char* pgopts; int /*<<< orphan*/  pgconfig; int /*<<< orphan*/  bindir; } ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SERVER_STOP_LOG_FILE ; 
 int /*<<< orphan*/  exec_prog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__ new_cluster ; 
 TYPE_1__ old_cluster ; 
 TYPE_2__ os_info ; 

void
stop_postmaster(bool in_atexit)
{
	ClusterInfo *cluster;

	if (os_info.running_cluster == &old_cluster)
		cluster = &old_cluster;
	else if (os_info.running_cluster == &new_cluster)
		cluster = &new_cluster;
	else
		return;					/* no cluster running */

	exec_prog(SERVER_STOP_LOG_FILE, NULL, !in_atexit, !in_atexit,
			  "\"%s/pg_ctl\" -w -D \"%s\" -o \"%s\" %s stop",
			  cluster->bindir, cluster->pgconfig,
			  cluster->pgopts ? cluster->pgopts : "",
			  in_atexit ? "-m fast" : "-m smart");

	os_info.running_cluster = NULL;
}