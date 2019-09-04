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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct posix_acl* get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (int /*<<< orphan*/ *,struct posix_acl*,void*,size_t) ; 

__attribute__((used)) static int
posix_acl_xattr_get(const struct xattr_handler *handler,
		    struct dentry *unused, struct inode *inode,
		    const char *name, void *value, size_t size)
{
	struct posix_acl *acl;
	int error;

	if (!IS_POSIXACL(inode))
		return -EOPNOTSUPP;
	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

	acl = get_acl(inode, handler->flags);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl == NULL)
		return -ENODATA;

	error = posix_acl_to_xattr(&init_user_ns, acl, value, size);
	posix_acl_release(acl);

	return error;
}