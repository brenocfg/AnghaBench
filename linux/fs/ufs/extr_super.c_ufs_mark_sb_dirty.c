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
struct ufs_sb_info {int work_queued; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  sync_work; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 struct ufs_sb_info* UFS_SB (struct super_block*) ; 
 int dirty_writeback_interval ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

void ufs_mark_sb_dirty(struct super_block *sb)
{
	struct ufs_sb_info *sbi = UFS_SB(sb);
	unsigned long delay;

	spin_lock(&sbi->work_lock);
	if (!sbi->work_queued) {
		delay = msecs_to_jiffies(dirty_writeback_interval * 10);
		queue_delayed_work(system_long_wq, &sbi->sync_work, delay);
		sbi->work_queued = 1;
	}
	spin_unlock(&sbi->work_lock);
}