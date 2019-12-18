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
struct inode {int /*<<< orphan*/  i_gid; } ;
struct iattr {unsigned int ia_valid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_size; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME_SET ; 
 unsigned int ATTR_FORCE ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_KILL_PRIV ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME_SET ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_TIMES_SET ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int EPERM ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chgrp_ok (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chown_ok (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 int inode_newsize_ok (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int security_inode_killpriv (struct dentry*) ; 

int setattr_prepare(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	unsigned int ia_valid = attr->ia_valid;

	/*
	 * First check size constraints.  These can't be overriden using
	 * ATTR_FORCE.
	 */
	if (ia_valid & ATTR_SIZE) {
		int error = inode_newsize_ok(inode, attr->ia_size);
		if (error)
			return error;
	}

	/* If force is set do it anyway. */
	if (ia_valid & ATTR_FORCE)
		goto kill_priv;

	/* Make sure a caller can chown. */
	if ((ia_valid & ATTR_UID) && !chown_ok(inode, attr->ia_uid))
		return -EPERM;

	/* Make sure caller can chgrp. */
	if ((ia_valid & ATTR_GID) && !chgrp_ok(inode, attr->ia_gid))
		return -EPERM;

	/* Make sure a caller can chmod. */
	if (ia_valid & ATTR_MODE) {
		if (!inode_owner_or_capable(inode))
			return -EPERM;
		/* Also check the setgid bit! */
		if (!in_group_p((ia_valid & ATTR_GID) ? attr->ia_gid :
				inode->i_gid) &&
		    !capable_wrt_inode_uidgid(inode, CAP_FSETID))
			attr->ia_mode &= ~S_ISGID;
	}

	/* Check for setting the inode time. */
	if (ia_valid & (ATTR_MTIME_SET | ATTR_ATIME_SET | ATTR_TIMES_SET)) {
		if (!inode_owner_or_capable(inode))
			return -EPERM;
	}

kill_priv:
	/* User has permission for the change */
	if (ia_valid & ATTR_KILL_PRIV) {
		int error;

		error = security_inode_killpriv(dentry);
		if (error)
			return error;
	}

	return 0;
}