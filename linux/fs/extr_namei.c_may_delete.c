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
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {int d_flags; TYPE_1__* d_parent; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_TYPE_CHILD_DELETE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DCACHE_NFSFS_RENAMED ; 
 int EBUSY ; 
 int EISDIR ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int EOVERFLOW ; 
 int EPERM ; 
 scalar_t__ HAS_UNMAPPED_ID (struct inode*) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  audit_inode_child (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_sticky (struct inode*,struct inode*) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 scalar_t__ d_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int inode_permission (struct inode*,int) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int may_delete(struct inode *dir, struct dentry *victim, bool isdir)
{
	struct inode *inode = d_backing_inode(victim);
	int error;

	if (d_is_negative(victim))
		return -ENOENT;
	BUG_ON(!inode);

	BUG_ON(victim->d_parent->d_inode != dir);

	/* Inode writeback is not safe when the uid or gid are invalid. */
	if (!uid_valid(inode->i_uid) || !gid_valid(inode->i_gid))
		return -EOVERFLOW;

	audit_inode_child(dir, victim, AUDIT_TYPE_CHILD_DELETE);

	error = inode_permission(dir, MAY_WRITE | MAY_EXEC);
	if (error)
		return error;
	if (IS_APPEND(dir))
		return -EPERM;

	if (check_sticky(dir, inode) || IS_APPEND(inode) ||
	    IS_IMMUTABLE(inode) || IS_SWAPFILE(inode) || HAS_UNMAPPED_ID(inode))
		return -EPERM;
	if (isdir) {
		if (!d_is_dir(victim))
			return -ENOTDIR;
		if (IS_ROOT(victim))
			return -EBUSY;
	} else if (d_is_dir(victim))
		return -EISDIR;
	if (IS_DEADDIR(dir))
		return -ENOENT;
	if (victim->d_flags & DCACHE_NFSFS_RENAMED)
		return -EBUSY;
	return 0;
}