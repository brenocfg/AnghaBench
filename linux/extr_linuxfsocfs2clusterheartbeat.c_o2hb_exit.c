#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_db_failedregions ; 
 int /*<<< orphan*/  o2hb_db_livenodes ; 
 int /*<<< orphan*/  o2hb_db_liveregions ; 
 int /*<<< orphan*/  o2hb_db_quorumregions ; 
 int /*<<< orphan*/  o2hb_debug_dir ; 
 int /*<<< orphan*/  o2hb_debug_failedregions ; 
 int /*<<< orphan*/  o2hb_debug_livenodes ; 
 int /*<<< orphan*/  o2hb_debug_liveregions ; 
 int /*<<< orphan*/  o2hb_debug_quorumregions ; 

void o2hb_exit(void)
{
	debugfs_remove(o2hb_debug_failedregions);
	debugfs_remove(o2hb_debug_quorumregions);
	debugfs_remove(o2hb_debug_liveregions);
	debugfs_remove(o2hb_debug_livenodes);
	debugfs_remove(o2hb_debug_dir);
	kfree(o2hb_db_livenodes);
	kfree(o2hb_db_liveregions);
	kfree(o2hb_db_quorumregions);
	kfree(o2hb_db_failedregions);
}