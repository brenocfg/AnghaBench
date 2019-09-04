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

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_NAME_SELINUX ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_copy_up_xattr(const char *name)
{
	/* The copy_up hook above sets the initial context on an inode, but we
	 * don't then want to overwrite it by blindly copying all the lower
	 * xattrs up.  Instead, we have to filter out SELinux-related xattrs.
	 */
	if (strcmp(name, XATTR_NAME_SELINUX) == 0)
		return 1; /* Discard */
	/*
	 * Any other attribute apart from SELINUX is not claimed, supported
	 * by selinux.
	 */
	return -EOPNOTSUPP;
}