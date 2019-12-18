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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_lock; } ;
struct iattr {int ia_valid; int ia_mode; } ;
struct TYPE_2__ {int attr_valid; int /*<<< orphan*/  attr_gid; int /*<<< orphan*/  attr_uid; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GOSSIP_UTILS_DEBUG ; 
 TYPE_1__* ORANGEFS_I (struct inode*) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_root_handle (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int orangefs_setattr_size (struct inode*,struct iattr*) ; 
 int posix_acl_chmod (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

int __orangefs_setattr(struct inode *inode, struct iattr *iattr)
{
	int ret;

	if (iattr->ia_valid & ATTR_MODE) {
		if (iattr->ia_mode & (S_ISVTX)) {
			if (is_root_handle(inode)) {
				/*
				 * allow sticky bit to be set on root (since
				 * it shows up that way by default anyhow),
				 * but don't show it to the server
				 */
				iattr->ia_mode -= S_ISVTX;
			} else {
				gossip_debug(GOSSIP_UTILS_DEBUG,
					     "User attempted to set sticky bit on non-root directory; returning EINVAL.\n");
				ret = -EINVAL;
				goto out;
			}
		}
		if (iattr->ia_mode & (S_ISUID)) {
			gossip_debug(GOSSIP_UTILS_DEBUG,
				     "Attempting to set setuid bit (not supported); returning EINVAL.\n");
			ret = -EINVAL;
			goto out;
		}
	}

	if (iattr->ia_valid & ATTR_SIZE) {
		ret = orangefs_setattr_size(inode, iattr);
		if (ret)
			goto out;
	}

again:
	spin_lock(&inode->i_lock);
	if (ORANGEFS_I(inode)->attr_valid) {
		if (uid_eq(ORANGEFS_I(inode)->attr_uid, current_fsuid()) &&
		    gid_eq(ORANGEFS_I(inode)->attr_gid, current_fsgid())) {
			ORANGEFS_I(inode)->attr_valid = iattr->ia_valid;
		} else {
			spin_unlock(&inode->i_lock);
			write_inode_now(inode, 1);
			goto again;
		}
	} else {
		ORANGEFS_I(inode)->attr_valid = iattr->ia_valid;
		ORANGEFS_I(inode)->attr_uid = current_fsuid();
		ORANGEFS_I(inode)->attr_gid = current_fsgid();
	}
	setattr_copy(inode, iattr);
	spin_unlock(&inode->i_lock);
	mark_inode_dirty(inode);

	if (iattr->ia_valid & ATTR_MODE)
		/* change mod on a file that has ACLs */
		ret = posix_acl_chmod(inode, inode->i_mode);

	ret = 0;
out:
	return ret;
}