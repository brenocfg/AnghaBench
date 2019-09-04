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
struct inode {scalar_t__ i_sb; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CHOWN ; 
 int ENOENT ; 
 int EPERM ; 
 int EXDEV ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct inode* d_inode (struct dentry*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int ocfs2_may_create (struct inode*,struct dentry*) ; 
 int ocfs2_reflink (struct dentry*,struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_vfs_reflink(struct dentry *old_dentry, struct inode *dir,
			     struct dentry *new_dentry, bool preserve)
{
	struct inode *inode = d_inode(old_dentry);
	int error;

	if (!inode)
		return -ENOENT;

	error = ocfs2_may_create(dir, new_dentry);
	if (error)
		return error;

	if (dir->i_sb != inode->i_sb)
		return -EXDEV;

	/*
	 * A reflink to an append-only or immutable file cannot be created.
	 */
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		return -EPERM;

	/* Only regular files can be reflinked. */
	if (!S_ISREG(inode->i_mode))
		return -EPERM;

	/*
	 * If the caller wants to preserve ownership, they require the
	 * rights to do so.
	 */
	if (preserve) {
		if (!uid_eq(current_fsuid(), inode->i_uid) && !capable(CAP_CHOWN))
			return -EPERM;
		if (!in_group_p(inode->i_gid) && !capable(CAP_CHOWN))
			return -EPERM;
	}

	/*
	 * If the caller is modifying any aspect of the attributes, they
	 * are not creating a snapshot.  They need read permission on the
	 * file.
	 */
	if (!preserve) {
		error = inode_permission(inode, MAY_READ);
		if (error)
			return error;
	}

	inode_lock(inode);
	error = dquot_initialize(dir);
	if (!error)
		error = ocfs2_reflink(old_dentry, dir, new_dentry, preserve);
	inode_unlock(inode);
	if (!error)
		fsnotify_create(dir, new_dentry);
	return error;
}