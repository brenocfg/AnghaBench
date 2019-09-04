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
struct inode {int i_generation; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  namebuf ;
struct TYPE_2__ {int /*<<< orphan*/  k_objectid; } ;

/* Variables and functions */
 int ENODATA ; 
 struct dentry* ERR_PTR (int) ; 
 TYPE_1__* INODE_PKEY (struct inode const*) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_XATTR ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 struct dentry* open_xa_root (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ xattr_may_create (int) ; 
 int xattr_mkdir (int /*<<< orphan*/ ,struct dentry*,int) ; 

__attribute__((used)) static struct dentry *open_xa_dir(const struct inode *inode, int flags)
{
	struct dentry *xaroot, *xadir;
	char namebuf[17];

	xaroot = open_xa_root(inode->i_sb, flags);
	if (IS_ERR(xaroot))
		return xaroot;

	snprintf(namebuf, sizeof(namebuf), "%X.%X",
		 le32_to_cpu(INODE_PKEY(inode)->k_objectid),
		 inode->i_generation);

	inode_lock_nested(d_inode(xaroot), I_MUTEX_XATTR);

	xadir = lookup_one_len(namebuf, xaroot, strlen(namebuf));
	if (!IS_ERR(xadir) && d_really_is_negative(xadir)) {
		int err = -ENODATA;

		if (xattr_may_create(flags))
			err = xattr_mkdir(d_inode(xaroot), xadir, 0700);
		if (err) {
			dput(xadir);
			xadir = ERR_PTR(err);
		}
	}

	inode_unlock(d_inode(xaroot));
	dput(xaroot);
	return xadir;
}