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
struct ocfs2_lock_holder {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_xattr_sem; int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int __ocfs2_reflink (struct dentry*,struct buffer_head*,struct inode*,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_create_inode_in_orphan (struct inode*,int /*<<< orphan*/ ,struct inode**) ; 
 int ocfs2_init_security_and_acl (struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int ocfs2_inode_lock_tracker (struct inode*,int /*<<< orphan*/ *,int,struct ocfs2_lock_holder*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock_tracker (struct inode*,int,struct ocfs2_lock_holder*,int) ; 
 int ocfs2_mv_orphaned_inode_to_new (struct inode*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  ocfs2_open_unlock (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree (int /*<<< orphan*/ ) ; 
 int ocfs2_rw_lock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_reflink(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *new_dentry, bool preserve)
{
	int error, had_lock;
	struct inode *inode = d_inode(old_dentry);
	struct buffer_head *old_bh = NULL;
	struct inode *new_orphan_inode = NULL;
	struct ocfs2_lock_holder oh;

	if (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb)))
		return -EOPNOTSUPP;


	error = ocfs2_create_inode_in_orphan(dir, inode->i_mode,
					     &new_orphan_inode);
	if (error) {
		mlog_errno(error);
		goto out;
	}

	error = ocfs2_rw_lock(inode, 1);
	if (error) {
		mlog_errno(error);
		goto out;
	}

	error = ocfs2_inode_lock(inode, &old_bh, 1);
	if (error) {
		mlog_errno(error);
		ocfs2_rw_unlock(inode, 1);
		goto out;
	}

	down_write(&OCFS2_I(inode)->ip_xattr_sem);
	down_write(&OCFS2_I(inode)->ip_alloc_sem);
	error = __ocfs2_reflink(old_dentry, old_bh,
				new_orphan_inode, preserve);
	up_write(&OCFS2_I(inode)->ip_alloc_sem);
	up_write(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock(inode, 1);
	ocfs2_rw_unlock(inode, 1);
	brelse(old_bh);

	if (error) {
		mlog_errno(error);
		goto out;
	}

	had_lock = ocfs2_inode_lock_tracker(new_orphan_inode, NULL, 1,
					    &oh);
	if (had_lock < 0) {
		error = had_lock;
		mlog_errno(error);
		goto out;
	}

	/* If the security isn't preserved, we need to re-initialize them. */
	if (!preserve) {
		error = ocfs2_init_security_and_acl(dir, new_orphan_inode,
						    &new_dentry->d_name);
		if (error)
			mlog_errno(error);
	}
	if (!error) {
		error = ocfs2_mv_orphaned_inode_to_new(dir, new_orphan_inode,
						       new_dentry);
		if (error)
			mlog_errno(error);
	}
	ocfs2_inode_unlock_tracker(new_orphan_inode, 1, &oh, had_lock);

out:
	if (new_orphan_inode) {
		/*
		 * We need to open_unlock the inode no matter whether we
		 * succeed or not, so that other nodes can delete it later.
		 */
		ocfs2_open_unlock(new_orphan_inode);
		if (error)
			iput(new_orphan_inode);
	}

	return error;
}