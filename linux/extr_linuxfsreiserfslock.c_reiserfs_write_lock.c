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
struct reiserfs_sb_info {scalar_t__ lock_owner; int /*<<< orphan*/  lock_depth; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

void reiserfs_write_lock(struct super_block *s)
{
	struct reiserfs_sb_info *sb_i = REISERFS_SB(s);

	if (sb_i->lock_owner != current) {
		mutex_lock(&sb_i->lock);
		sb_i->lock_owner = current;
	}

	/* No need to protect it, only the current task touches it */
	sb_i->lock_depth++;
}