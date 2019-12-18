#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* pgdata; int /*<<< orphan*/  major_version; } ;
typedef  TYPE_1__ ClusterInfo ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_single_dir (char const*,char*) ; 
 int /*<<< orphan*/  get_major_server_version (TYPE_1__*) ; 

__attribute__((used)) static void
check_data_dir(ClusterInfo *cluster)
{
	const char *pg_data = cluster->pgdata;

	/* get the cluster version */
	cluster->major_version = get_major_server_version(cluster);

	check_single_dir(pg_data, "");
	check_single_dir(pg_data, "base");
	check_single_dir(pg_data, "global");
	check_single_dir(pg_data, "pg_multixact");
	check_single_dir(pg_data, "pg_subtrans");
	check_single_dir(pg_data, "pg_tblspc");
	check_single_dir(pg_data, "pg_twophase");

	/* pg_xlog has been renamed to pg_wal in v10 */
	if (GET_MAJOR_VERSION(cluster->major_version) < 1000)
		check_single_dir(pg_data, "pg_xlog");
	else
		check_single_dir(pg_data, "pg_wal");

	/* pg_clog has been renamed to pg_xact in v10 */
	if (GET_MAJOR_VERSION(cluster->major_version) < 1000)
		check_single_dir(pg_data, "pg_clog");
	else
		check_single_dir(pg_data, "pg_xact");
}