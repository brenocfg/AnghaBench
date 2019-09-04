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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_root; struct dentry* priv_root; } ;

/* Variables and functions */
 int ENODATA ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  I_MUTEX_XATTR ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ xattr_may_create (int) ; 
 int xattr_mkdir (int /*<<< orphan*/ ,struct dentry*,int) ; 

__attribute__((used)) static struct dentry *open_xa_root(struct super_block *sb, int flags)
{
	struct dentry *privroot = REISERFS_SB(sb)->priv_root;
	struct dentry *xaroot;

	if (d_really_is_negative(privroot))
		return ERR_PTR(-ENODATA);

	inode_lock_nested(d_inode(privroot), I_MUTEX_XATTR);

	xaroot = dget(REISERFS_SB(sb)->xattr_root);
	if (!xaroot)
		xaroot = ERR_PTR(-ENODATA);
	else if (d_really_is_negative(xaroot)) {
		int err = -ENODATA;

		if (xattr_may_create(flags))
			err = xattr_mkdir(d_inode(privroot), xaroot, 0700);
		if (err) {
			dput(xaroot);
			xaroot = ERR_PTR(err);
		}
	}

	inode_unlock(d_inode(privroot));
	return xaroot;
}