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
struct inode {int dummy; } ;

/* Variables and functions */
 int ATTR_ROOT ; 

void
xfs_forget_acl(
	struct inode		*inode,
	const char		*name,
	int			xflags)
{
	/*
	 * Invalidate any cached ACLs if the user has bypassed the ACL
	 * interface. We don't validate the content whatsoever so it is caller
	 * responsibility to provide data in valid format and ensure i_mode is
	 * consistent.
	 */
	if (xflags & ATTR_ROOT) {
#ifdef CONFIG_XFS_POSIX_ACL
		if (!strcmp(name, SGI_ACL_FILE))
			forget_cached_acl(inode, ACL_TYPE_ACCESS);
		else if (!strcmp(name, SGI_ACL_DEFAULT))
			forget_cached_acl(inode, ACL_TYPE_DEFAULT);
#endif
	}
}