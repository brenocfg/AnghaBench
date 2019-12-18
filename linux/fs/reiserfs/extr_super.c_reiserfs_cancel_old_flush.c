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
struct reiserfs_sb_info {int work_queued; int /*<<< orphan*/  old_work; int /*<<< orphan*/  old_work_lock; } ;

/* Variables and functions */
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void reiserfs_cancel_old_flush(struct super_block *s)
{
	struct reiserfs_sb_info *sbi = REISERFS_SB(s);

	spin_lock(&sbi->old_work_lock);
	/* Make sure no new flushes will be queued */
	sbi->work_queued = 2;
	spin_unlock(&sbi->old_work_lock);
	cancel_delayed_work_sync(&REISERFS_SB(s)->old_work);
}