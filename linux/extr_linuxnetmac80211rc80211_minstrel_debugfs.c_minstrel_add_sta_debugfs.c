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
struct minstrel_sta_info {void* dbg_stats_csv; void* dbg_stats; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 void* debugfs_create_file (char*,int,struct dentry*,struct minstrel_sta_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minstrel_stat_csv_fops ; 
 int /*<<< orphan*/  minstrel_stat_fops ; 

void
minstrel_add_sta_debugfs(void *priv, void *priv_sta, struct dentry *dir)
{
	struct minstrel_sta_info *mi = priv_sta;

	mi->dbg_stats = debugfs_create_file("rc_stats", 0444, dir, mi,
					    &minstrel_stat_fops);

	mi->dbg_stats_csv = debugfs_create_file("rc_stats_csv", 0444, dir, mi,
						&minstrel_stat_csv_fops);
}