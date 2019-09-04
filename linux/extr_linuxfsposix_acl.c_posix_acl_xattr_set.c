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
struct xattr_handler {int /*<<< orphan*/  flags; } ;
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct posix_acl* posix_acl_from_xattr (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int set_posix_acl (struct inode*,int /*<<< orphan*/ ,struct posix_acl*) ; 

__attribute__((used)) static int
posix_acl_xattr_set(const struct xattr_handler *handler,
		    struct dentry *unused, struct inode *inode,
		    const char *name, const void *value,
		    size_t size, int flags)
{
	struct posix_acl *acl = NULL;
	int ret;

	if (value) {
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);
	}
	ret = set_posix_acl(inode, handler->flags, acl);
	posix_acl_release(acl);
	return ret;
}