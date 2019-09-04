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
struct xattr_handler {int dummy; } ;

/* Variables and functions */
#define  JFFS2_XPREFIX_TRUSTED 129 
#define  JFFS2_XPREFIX_USER 128 
 struct xattr_handler jffs2_trusted_xattr_handler ; 
 struct xattr_handler jffs2_user_xattr_handler ; 

__attribute__((used)) static const struct xattr_handler *xprefix_to_handler(int xprefix) {
	const struct xattr_handler *ret;

	switch (xprefix) {
	case JFFS2_XPREFIX_USER:
		ret = &jffs2_user_xattr_handler;
		break;
#ifdef CONFIG_JFFS2_FS_SECURITY
	case JFFS2_XPREFIX_SECURITY:
		ret = &jffs2_security_xattr_handler;
		break;
#endif
#ifdef CONFIG_JFFS2_FS_POSIX_ACL
	case JFFS2_XPREFIX_ACL_ACCESS:
		ret = &posix_acl_access_xattr_handler;
		break;
	case JFFS2_XPREFIX_ACL_DEFAULT:
		ret = &posix_acl_default_xattr_handler;
		break;
#endif
	case JFFS2_XPREFIX_TRUSTED:
		ret = &jffs2_trusted_xattr_handler;
		break;
	default:
		ret = NULL;
		break;
	}
	return ret;
}