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
struct TYPE_2__ {int /*<<< orphan*/  major_version; } ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_9_0_populate_pg_largeobject_metadata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  new_cluster ; 
 int /*<<< orphan*/  old_9_6_invalidate_hash_indexes (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ old_cluster ; 
 int /*<<< orphan*/  start_postmaster (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stop_postmaster (int) ; 

void
issue_warnings_and_set_wal_level(void)
{
	/*
	 * We unconditionally start/stop the new server because pg_resetwal -o set
	 * wal_level to 'minimum'.  If the user is upgrading standby servers using
	 * the rsync instructions, they will need pg_upgrade to write its final
	 * WAL record showing wal_level as 'replica'.
	 */
	start_postmaster(&new_cluster, true);

	/* Create dummy large object permissions for old < PG 9.0? */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 804)
		new_9_0_populate_pg_largeobject_metadata(&new_cluster, false);

	/* Reindex hash indexes for old < 10.0 */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 906)
		old_9_6_invalidate_hash_indexes(&new_cluster, false);

	stop_postmaster(false);
}