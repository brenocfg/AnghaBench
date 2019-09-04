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
struct inode {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  user_ns; scalar_t__ no_setxattr; int /*<<< orphan*/  posix_acl; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 char* XATTR_NAME_POSIX_ACL_ACCESS ; 
 char* XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  forget_all_cached_acls (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int fuse_removexattr (struct inode*,char const*) ; 
 int fuse_setxattr (struct inode*,char const*,void*,size_t,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int posix_acl_to_xattr (int /*<<< orphan*/ ,struct posix_acl*,void*,size_t) ; 
 size_t posix_acl_xattr_size (int /*<<< orphan*/ ) ; 

int fuse_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	const char *name;
	int ret;

	if (!fc->posix_acl || fc->no_setxattr)
		return -EOPNOTSUPP;

	if (type == ACL_TYPE_ACCESS)
		name = XATTR_NAME_POSIX_ACL_ACCESS;
	else if (type == ACL_TYPE_DEFAULT)
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
	else
		return -EINVAL;

	if (acl) {
		/*
		 * Fuse userspace is responsible for updating access
		 * permissions in the inode, if needed. fuse_setxattr
		 * invalidates the inode attributes, which will force
		 * them to be refreshed the next time they are used,
		 * and it also updates i_ctime.
		 */
		size_t size = posix_acl_xattr_size(acl->a_count);
		void *value;

		if (size > PAGE_SIZE)
			return -E2BIG;

		value = kmalloc(size, GFP_KERNEL);
		if (!value)
			return -ENOMEM;

		ret = posix_acl_to_xattr(fc->user_ns, acl, value, size);
		if (ret < 0) {
			kfree(value);
			return ret;
		}

		ret = fuse_setxattr(inode, name, value, size, 0);
		kfree(value);
	} else {
		ret = fuse_removexattr(inode, name);
	}
	forget_all_cached_acls(inode);
	fuse_invalidate_attr(inode);

	return ret;
}