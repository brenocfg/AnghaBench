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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct btrfs_trans_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int __btrfs_set_acl (struct btrfs_trans_handle*,struct inode*,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_no_acl (struct inode*) ; 
 int posix_acl_create (struct inode*,int /*<<< orphan*/ *,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int btrfs_init_acl(struct btrfs_trans_handle *trans,
		   struct inode *inode, struct inode *dir)
{
	struct posix_acl *default_acl, *acl;
	int ret = 0;

	/* this happens with subvols */
	if (!dir)
		return 0;

	ret = posix_acl_create(dir, &inode->i_mode, &default_acl, &acl);
	if (ret)
		return ret;

	if (default_acl) {
		ret = __btrfs_set_acl(trans, inode, default_acl,
				      ACL_TYPE_DEFAULT);
		posix_acl_release(default_acl);
	}

	if (acl) {
		if (!ret)
			ret = __btrfs_set_acl(trans, inode, acl,
					      ACL_TYPE_ACCESS);
		posix_acl_release(acl);
	}

	if (!default_acl && !acl)
		cache_no_acl(inode);
	return ret;
}