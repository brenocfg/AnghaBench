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
struct xattr_handler {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct v9fs_session_info {int flags; } ;
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int V9FS_ACCESS_CLIENT ; 
 int V9FS_ACCESS_MASK ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (int /*<<< orphan*/ *,struct posix_acl*,void*,size_t) ; 
 struct v9fs_session_info* v9fs_dentry2v9ses (struct dentry*) ; 
 struct posix_acl* v9fs_get_cached_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int v9fs_xattr_get (struct dentry*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int v9fs_xattr_get_acl(const struct xattr_handler *handler,
			      struct dentry *dentry, struct inode *inode,
			      const char *name, void *buffer, size_t size)
{
	struct v9fs_session_info *v9ses;
	struct posix_acl *acl;
	int error;

	v9ses = v9fs_dentry2v9ses(dentry);
	/*
	 * We allow set/get/list of acl when access=client is not specified
	 */
	if ((v9ses->flags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CLIENT)
		return v9fs_xattr_get(dentry, handler->name, buffer, size);

	acl = v9fs_get_cached_acl(inode, handler->flags);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl == NULL)
		return -ENODATA;
	error = posix_acl_to_xattr(&init_user_ns, acl, buffer, size);
	posix_acl_release(acl);

	return error;
}