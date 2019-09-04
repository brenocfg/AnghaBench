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
struct reiserfs_sb_info {int lock_depth; int /*<<< orphan*/  lock; int /*<<< orphan*/ * lock_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void reiserfs_write_unlock(struct super_block *s)
{
	struct reiserfs_sb_info *sb_i = REISERFS_SB(s);

	/*
	 * Are we unlocking without even holding the lock?
	 * Such a situation must raise a BUG() if we don't want
	 * to corrupt the data.
	 */
	BUG_ON(sb_i->lock_owner != current);

	if (--sb_i->lock_depth == -1) {
		sb_i->lock_owner = NULL;
		mutex_unlock(&sb_i->lock);
	}
}