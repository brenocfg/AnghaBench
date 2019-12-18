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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int AFFS_MOUNT_SF_IMMUTABLE ; 
 int AFFS_MOUNT_SF_SETMODE ; 
 TYPE_1__* AFFS_SB (int /*<<< orphan*/ ) ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int EPERM ; 
 int /*<<< orphan*/  SF_QUIET ; 
 int /*<<< orphan*/  SF_SETGID ; 
 int /*<<< orphan*/  SF_SETUID ; 
 int /*<<< orphan*/  affs_mode_to_prot (struct inode*) ; 
 scalar_t__ affs_test_opt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_truncate (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 

int
affs_notify_change(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	int error;

	pr_debug("notify_change(%lu,0x%x)\n", inode->i_ino, attr->ia_valid);

	error = setattr_prepare(dentry, attr);
	if (error)
		goto out;

	if (((attr->ia_valid & ATTR_UID) &&
	      affs_test_opt(AFFS_SB(inode->i_sb)->s_flags, SF_SETUID)) ||
	    ((attr->ia_valid & ATTR_GID) &&
	      affs_test_opt(AFFS_SB(inode->i_sb)->s_flags, SF_SETGID)) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     (AFFS_SB(inode->i_sb)->s_flags &
	      (AFFS_MOUNT_SF_SETMODE | AFFS_MOUNT_SF_IMMUTABLE)))) {
		if (!affs_test_opt(AFFS_SB(inode->i_sb)->s_flags, SF_QUIET))
			error = -EPERM;
		goto out;
	}

	if ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_read(inode)) {
		error = inode_newsize_ok(inode, attr->ia_size);
		if (error)
			return error;

		truncate_setsize(inode, attr->ia_size);
		affs_truncate(inode);
	}

	setattr_copy(inode, attr);
	mark_inode_dirty(inode);

	if (attr->ia_valid & ATTR_MODE)
		affs_mode_to_prot(inode);
out:
	return error;
}