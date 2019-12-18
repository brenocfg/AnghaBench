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
struct xattr_handler {int flags; int /*<<< orphan*/  name; } ;
struct v9fs_session_info {int flags; } ;
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct iattr {int /*<<< orphan*/  ia_valid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  member_0; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_user_ns; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  ATTR_MODE ; 
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int V9FS_ACCESS_CLIENT ; 
 int V9FS_ACCESS_MASK ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 struct posix_acl* posix_acl_from_xattr (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_update_mode (struct inode*,int /*<<< orphan*/ *,struct posix_acl**) ; 
 int posix_acl_valid (int /*<<< orphan*/ ,struct posix_acl*) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 
 struct v9fs_session_info* v9fs_dentry2v9ses (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_vfs_setattr_dotl (struct dentry*,struct iattr*) ; 
 int v9fs_xattr_set (struct dentry*,int /*<<< orphan*/ ,void const*,size_t,int) ; 

__attribute__((used)) static int v9fs_xattr_set_acl(const struct xattr_handler *handler,
			      struct dentry *dentry, struct inode *inode,
			      const char *name, const void *value,
			      size_t size, int flags)
{
	int retval;
	struct posix_acl *acl;
	struct v9fs_session_info *v9ses;

	v9ses = v9fs_dentry2v9ses(dentry);
	/*
	 * set the attribute on the remote. Without even looking at the
	 * xattr value. We leave it to the server to validate
	 */
	if ((v9ses->flags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CLIENT)
		return v9fs_xattr_set(dentry, handler->name, value, size,
				      flags);

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;
	if (!inode_owner_or_capable(inode))
		return -EPERM;
	if (value) {
		/* update the cached acl value */
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);
		else if (acl) {
			retval = posix_acl_valid(inode->i_sb->s_user_ns, acl);
			if (retval)
				goto err_out;
		}
	} else
		acl = NULL;

	switch (handler->flags) {
	case ACL_TYPE_ACCESS:
		if (acl) {
			struct iattr iattr = { 0 };
			struct posix_acl *old_acl = acl;

			retval = posix_acl_update_mode(inode, &iattr.ia_mode, &acl);
			if (retval)
				goto err_out;
			if (!acl) {
				/*
				 * ACL can be represented
				 * by the mode bits. So don't
				 * update ACL.
				 */
				posix_acl_release(old_acl);
				value = NULL;
				size = 0;
			}
			iattr.ia_valid = ATTR_MODE;
			/* FIXME should we update ctime ?
			 * What is the following setxattr update the
			 * mode ?
			 */
			v9fs_vfs_setattr_dotl(dentry, &iattr);
		}
		break;
	case ACL_TYPE_DEFAULT:
		if (!S_ISDIR(inode->i_mode)) {
			retval = acl ? -EINVAL : 0;
			goto err_out;
		}
		break;
	default:
		BUG();
	}
	retval = v9fs_xattr_set(dentry, handler->name, value, size, flags);
	if (!retval)
		set_cached_acl(inode, handler->flags, acl);
err_out:
	posix_acl_release(acl);
	return retval;
}