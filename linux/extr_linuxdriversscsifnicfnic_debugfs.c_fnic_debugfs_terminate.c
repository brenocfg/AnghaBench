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
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ fc_trc_flag ; 
 int /*<<< orphan*/ * fnic_stats_debugfs_root ; 
 int /*<<< orphan*/ * fnic_trace_debugfs_root ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 

void fnic_debugfs_terminate(void)
{
	debugfs_remove(fnic_stats_debugfs_root);
	fnic_stats_debugfs_root = NULL;

	debugfs_remove(fnic_trace_debugfs_root);
	fnic_trace_debugfs_root = NULL;

	if (fc_trc_flag)
		vfree(fc_trc_flag);
}