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
struct super_block {int s_flags; } ;
struct reiserfs_sb_info {int work_queued; int /*<<< orphan*/  old_work_lock; int /*<<< orphan*/  old_work; } ;

/* Variables and functions */
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int SB_ACTIVE ; 
 int dirty_writeback_interval ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_long_wq ; 

void reiserfs_schedule_old_flush(struct super_block *s)
{
	struct reiserfs_sb_info *sbi = REISERFS_SB(s);
	unsigned long delay;

	/*
	 * Avoid scheduling flush when sb is being shut down. It can race
	 * with journal shutdown and free still queued delayed work.
	 */
	if (sb_rdonly(s) || !(s->s_flags & SB_ACTIVE))
		return;

	spin_lock(&sbi->old_work_lock);
	if (!sbi->work_queued) {
		delay = msecs_to_jiffies(dirty_writeback_interval * 10);
		queue_delayed_work(system_long_wq, &sbi->old_work, delay);
		sbi->work_queued = 1;
	}
	spin_unlock(&sbi->old_work_lock);
}