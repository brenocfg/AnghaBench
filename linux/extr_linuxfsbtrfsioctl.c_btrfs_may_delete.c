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
struct inode {int dummy; } ;
struct dentry {int d_flags; struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_TYPE_CHILD_DELETE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DCACHE_NFSFS_RENAMED ; 
 int EBUSY ; 
 int EISDIR ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int EPERM ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  audit_inode_child (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_sticky (struct inode*,struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int inode_permission (struct inode*,int) ; 

__attribute__((used)) static int btrfs_may_delete(struct inode *dir, struct dentry *victim, int isdir)
{
	int error;

	if (d_really_is_negative(victim))
		return -ENOENT;

	BUG_ON(d_inode(victim->d_parent) != dir);
	audit_inode_child(dir, victim, AUDIT_TYPE_CHILD_DELETE);

	error = inode_permission(dir, MAY_WRITE | MAY_EXEC);
	if (error)
		return error;
	if (IS_APPEND(dir))
		return -EPERM;
	if (check_sticky(dir, d_inode(victim)) || IS_APPEND(d_inode(victim)) ||
	    IS_IMMUTABLE(d_inode(victim)) || IS_SWAPFILE(d_inode(victim)))
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