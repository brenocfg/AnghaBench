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
struct super_block {int dummy; } ;
struct affs_sb_info {int work_queued; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  sb_work; } ;

/* Variables and functions */
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int dirty_writeback_interval ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

void affs_mark_sb_dirty(struct super_block *sb)
{
	struct affs_sb_info *sbi = AFFS_SB(sb);
	unsigned long delay;

	if (sb_rdonly(sb))
	       return;

	spin_lock(&sbi->work_lock);
	if (!sbi->work_queued) {
	       delay = msecs_to_jiffies(dirty_writeback_interval * 10);
	       queue_delayed_work(system_long_wq, &sbi->sb_work, delay);
	       sbi->work_queued = 1;
	}
	spin_unlock(&sbi->work_lock);
}