#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_lock; } ;
struct ocfs2_inode_info {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_flags; } ;
struct ocfs2_dentry_lock {int dl_count; TYPE_1__* dl_inode; int /*<<< orphan*/  dl_parent_blkno; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int DLM_LOCK_PR ; 
 struct ocfs2_inode_info* OCFS2_I (TYPE_1__*) ; 
 int /*<<< orphan*/  OCFS2_INODE_MAYBE_ORPHANED ; 
 int OCFS2_LOCK_FREEING ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int UNBLOCK_CONTINUE ; 
 int UNBLOCK_CONTINUE_POST ; 
 int UNBLOCK_STOP_POST ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  dentry_attach_lock ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 struct dentry* ocfs2_find_local_alias (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct ocfs2_dentry_lock* ocfs2_lock_res_dl (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ocfs2_dentry_convert_worker(struct ocfs2_lock_res *lockres,
				       int blocking)
{
	struct ocfs2_dentry_lock *dl = ocfs2_lock_res_dl(lockres);
	struct ocfs2_inode_info *oi = OCFS2_I(dl->dl_inode);
	struct dentry *dentry;
	unsigned long flags;
	int extra_ref = 0;

	/*
	 * This node is blocking another node from getting a read
	 * lock. This happens when we've renamed within a
	 * directory. We've forced the other nodes to d_delete(), but
	 * we never actually dropped our lock because it's still
	 * valid. The downconvert code will retain a PR for this node,
	 * so there's no further work to do.
	 */
	if (blocking == DLM_LOCK_PR)
		return UNBLOCK_CONTINUE;

	/*
	 * Mark this inode as potentially orphaned. The code in
	 * ocfs2_delete_inode() will figure out whether it actually
	 * needs to be freed or not.
	 */
	spin_lock(&oi->ip_lock);
	oi->ip_flags |= OCFS2_INODE_MAYBE_ORPHANED;
	spin_unlock(&oi->ip_lock);

	/*
	 * Yuck. We need to make sure however that the check of
	 * OCFS2_LOCK_FREEING and the extra reference are atomic with
	 * respect to a reference decrement or the setting of that
	 * flag.
	 */
	spin_lock_irqsave(&lockres->l_lock, flags);
	spin_lock(&dentry_attach_lock);
	if (!(lockres->l_flags & OCFS2_LOCK_FREEING)
	    && dl->dl_count) {
		dl->dl_count++;
		extra_ref = 1;
	}
	spin_unlock(&dentry_attach_lock);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	mlog(0, "extra_ref = %d\n", extra_ref);

	/*
	 * We have a process waiting on us in ocfs2_dentry_iput(),
	 * which means we can't have any more outstanding
	 * aliases. There's no need to do any more work.
	 */
	if (!extra_ref)
		return UNBLOCK_CONTINUE;

	spin_lock(&dentry_attach_lock);
	while (1) {
		dentry = ocfs2_find_local_alias(dl->dl_inode,
						dl->dl_parent_blkno, 1);
		if (!dentry)
			break;
		spin_unlock(&dentry_attach_lock);

		if (S_ISDIR(dl->dl_inode->i_mode))
			shrink_dcache_parent(dentry);

		mlog(0, "d_delete(%pd);\n", dentry);

		/*
		 * The following dcache calls may do an
		 * iput(). Normally we don't want that from the
		 * downconverting thread, but in this case it's ok
		 * because the requesting node already has an
		 * exclusive lock on the inode, so it can't be queued
		 * for a downconvert.
		 */
		d_delete(dentry);
		dput(dentry);

		spin_lock(&dentry_attach_lock);
	}
	spin_unlock(&dentry_attach_lock);

	/*
	 * If we are the last holder of this dentry lock, there is no
	 * reason to downconvert so skip straight to the unlock.
	 */
	if (dl->dl_count == 1)
		return UNBLOCK_STOP_POST;

	return UNBLOCK_CONTINUE_POST;
}