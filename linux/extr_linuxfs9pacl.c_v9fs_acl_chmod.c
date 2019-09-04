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
struct posix_acl {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int __posix_acl_chmod (struct posix_acl**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int /*<<< orphan*/ ,struct posix_acl*) ; 
 struct posix_acl* v9fs_get_cached_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int v9fs_set_acl (struct p9_fid*,int /*<<< orphan*/ ,struct posix_acl*) ; 

int v9fs_acl_chmod(struct inode *inode, struct p9_fid *fid)
{
	int retval = 0;
	struct posix_acl *acl;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;
	acl = v9fs_get_cached_acl(inode, ACL_TYPE_ACCESS);
	if (acl) {
		retval = __posix_acl_chmod(&acl, GFP_KERNEL, inode->i_mode);
		if (retval)
			return retval;
		set_cached_acl(inode, ACL_TYPE_ACCESS, acl);
		retval = v9fs_set_acl(fid, ACL_TYPE_ACCESS, acl);
		posix_acl_release(acl);
	}
	return retval;
}