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
struct posix_acl {int /*<<< orphan*/  a_count; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct btrfs_trans_handle {int dummy; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 char* XATTR_NAME_POSIX_ACL_ACCESS ; 
 char* XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int btrfs_setxattr (struct btrfs_trans_handle*,struct inode*,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int btrfs_setxattr_trans (struct inode*,char const*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_nofs_restore (unsigned int) ; 
 unsigned int memalloc_nofs_save () ; 
 int posix_acl_to_xattr (int /*<<< orphan*/ *,struct posix_acl*,char*,int) ; 
 int posix_acl_xattr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static int __btrfs_set_acl(struct btrfs_trans_handle *trans,
			 struct inode *inode, struct posix_acl *acl, int type)
{
	int ret, size = 0;
	const char *name;
	char *value = NULL;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		if (!S_ISDIR(inode->i_mode))
			return acl ? -EINVAL : 0;
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		break;
	default:
		return -EINVAL;
	}

	if (acl) {
		unsigned int nofs_flag;

		size = posix_acl_xattr_size(acl->a_count);
		/*
		 * We're holding a transaction handle, so use a NOFS memory
		 * allocation context to avoid deadlock if reclaim happens.
		 */
		nofs_flag = memalloc_nofs_save();
		value = kmalloc(size, GFP_KERNEL);
		memalloc_nofs_restore(nofs_flag);
		if (!value) {
			ret = -ENOMEM;
			goto out;
		}

		ret = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		if (ret < 0)
			goto out;
	}

	if (trans)
		ret = btrfs_setxattr(trans, inode, name, value, size, 0);
	else
		ret = btrfs_setxattr_trans(inode, name, value, size, 0);

out:
	kfree(value);

	if (!ret)
		set_cached_acl(inode, type, acl);

	return ret;
}