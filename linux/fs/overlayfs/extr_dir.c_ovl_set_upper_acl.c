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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FS_POSIX_ACL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XATTR_CREATE ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int posix_acl_to_xattr (int /*<<< orphan*/ *,struct posix_acl const*,void*,size_t) ; 
 size_t posix_acl_xattr_size (int /*<<< orphan*/ ) ; 
 int vfs_setxattr (struct dentry*,char const*,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_set_upper_acl(struct dentry *upperdentry, const char *name,
			     const struct posix_acl *acl)
{
	void *buffer;
	size_t size;
	int err;

	if (!IS_ENABLED(CONFIG_FS_POSIX_ACL) || !acl)
		return 0;

	size = posix_acl_xattr_size(acl->a_count);
	buffer = kmalloc(size, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	err = posix_acl_to_xattr(&init_user_ns, acl, buffer, size);
	if (err < 0)
		goto out_free;

	err = vfs_setxattr(upperdentry, name, buffer, size, XATTR_CREATE);
out_free:
	kfree(buffer);
	return err;
}