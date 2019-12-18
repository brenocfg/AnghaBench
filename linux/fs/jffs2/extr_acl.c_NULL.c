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
typedef  int /*<<< orphan*/  umode_t ;
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mode; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int ATTR_CTIME ; 
 int ATTR_MODE ; 
 int EACCES ; 
 int EINVAL ; 
 int JFFS2_XPREFIX_ACL_ACCESS ; 
 int JFFS2_XPREFIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int __jffs2_set_acl (struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int jffs2_do_setattr (struct inode*,struct iattr*) ; 
 int posix_acl_update_mode (struct inode*,int /*<<< orphan*/ *,struct posix_acl**) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

int jffs2_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	int rc, xprefix;

	switch (type) {
	case ACL_TYPE_ACCESS:
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		if (acl) {
			umode_t mode;

			rc = posix_acl_update_mode(inode, &mode, &acl);
			if (rc)
				return rc;
			if (inode->i_mode != mode) {
				struct iattr attr;

				attr.ia_valid = ATTR_MODE | ATTR_CTIME;
				attr.ia_mode = mode;
				attr.ia_ctime = current_time(inode);
				rc = jffs2_do_setattr(inode, &attr);
				if (rc < 0)
					return rc;
			}
		}
		break;
	case ACL_TYPE_DEFAULT:
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		if (!S_ISDIR(inode->i_mode))
			return acl ? -EACCES : 0;
		break;
	default:
		return -EINVAL;
	}
	rc = __jffs2_set_acl(inode, xprefix, acl);
	if (!rc)
		set_cached_acl(inode, type, acl);
	return rc;
}