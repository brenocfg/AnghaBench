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
struct xattr_handler {int flags; } ;
struct inode {int dummy; } ;
struct erofs_sb_info {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 struct erofs_sb_info* EROFS_I_SB (struct inode*) ; 
#define  EROFS_XATTR_INDEX_SECURITY 130 
#define  EROFS_XATTR_INDEX_TRUSTED 129 
#define  EROFS_XATTR_INDEX_USER 128 
 int /*<<< orphan*/  XATTR_USER ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int erofs_getxattr (struct inode*,int,char const*,void*,size_t) ; 
 int /*<<< orphan*/  test_opt (struct erofs_sb_info* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int erofs_xattr_generic_get(const struct xattr_handler *handler,
				   struct dentry *unused, struct inode *inode,
				   const char *name, void *buffer, size_t size)
{
	struct erofs_sb_info *const sbi = EROFS_I_SB(inode);

	switch (handler->flags) {
	case EROFS_XATTR_INDEX_USER:
		if (!test_opt(sbi, XATTR_USER))
			return -EOPNOTSUPP;
		break;
	case EROFS_XATTR_INDEX_TRUSTED:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		break;
	case EROFS_XATTR_INDEX_SECURITY:
		break;
	default:
		return -EINVAL;
	}

	return erofs_getxattr(inode, handler->flags, name, buffer, size);
}