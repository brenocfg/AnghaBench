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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  OVL_XATTR_METACOPY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int) ; 
 int vfs_getxattr (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ovl_check_metacopy_xattr(struct dentry *dentry)
{
	int res;

	/* Only regular files can have metacopy xattr */
	if (!S_ISREG(d_inode(dentry)->i_mode))
		return 0;

	res = vfs_getxattr(dentry, OVL_XATTR_METACOPY, NULL, 0);
	if (res < 0) {
		if (res == -ENODATA || res == -EOPNOTSUPP)
			return 0;
		goto out;
	}

	return 1;
out:
	pr_warn_ratelimited("overlayfs: failed to get metacopy (%i)\n", res);
	return res;
}