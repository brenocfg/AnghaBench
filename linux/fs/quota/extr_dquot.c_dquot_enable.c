#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_umount; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 unsigned int DQUOT_LIMITS_ENABLED ; 
 unsigned int DQUOT_SUSPENDED ; 
 unsigned int DQUOT_USAGE_ENABLED ; 
 int EBUSY ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_state_lock ; 
 int /*<<< orphan*/  dquot_state_flag (unsigned int,int) ; 
 TYPE_1__* sb_dqopt (struct super_block*) ; 
 scalar_t__ sb_has_quota_limits_enabled (struct super_block*,int) ; 
 scalar_t__ sb_has_quota_loaded (struct super_block*,int) ; 
 scalar_t__ sb_has_quota_usage_enabled (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int vfs_load_quota_inode (struct inode*,int,int,unsigned int) ; 

int dquot_enable(struct inode *inode, int type, int format_id,
		 unsigned int flags)
{
	struct super_block *sb = inode->i_sb;

	/* Just unsuspend quotas? */
	BUG_ON(flags & DQUOT_SUSPENDED);
	/* s_umount should be held in exclusive mode */
	if (WARN_ON_ONCE(down_read_trylock(&sb->s_umount)))
		up_read(&sb->s_umount);

	if (!flags)
		return 0;
	/* Just updating flags needed? */
	if (sb_has_quota_loaded(sb, type)) {
		if (flags & DQUOT_USAGE_ENABLED &&
		    sb_has_quota_usage_enabled(sb, type))
			return -EBUSY;
		if (flags & DQUOT_LIMITS_ENABLED &&
		    sb_has_quota_limits_enabled(sb, type))
			return -EBUSY;
		spin_lock(&dq_state_lock);
		sb_dqopt(sb)->flags |= dquot_state_flag(flags, type);
		spin_unlock(&dq_state_lock);
		return 0;
	}

	return vfs_load_quota_inode(inode, type, format_id, flags);
}