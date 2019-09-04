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
struct reiserfs_sb_info {int /*<<< orphan*/  old_work_lock; scalar_t__ work_queued; } ;

/* Variables and functions */
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_allow_writes (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reiserfs_unfreeze(struct super_block *s)
{
	struct reiserfs_sb_info *sbi = REISERFS_SB(s);

	reiserfs_allow_writes(s);
	spin_lock(&sbi->old_work_lock);
	/* Allow old_work to run again */
	sbi->work_queued = 0;
	spin_unlock(&sbi->old_work_lock);
	return 0;
}