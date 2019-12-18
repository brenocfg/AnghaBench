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
 char const* XATTR_NAME_POSIX_ACL_ACCESS ; 
 char const* XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

int posix_xattr_acl(const char *xattr)
{
	int xattr_len = strlen(xattr);

	if ((strlen(XATTR_NAME_POSIX_ACL_ACCESS) == xattr_len)
	     && (strncmp(XATTR_NAME_POSIX_ACL_ACCESS, xattr, xattr_len) == 0))
		return 1;
	if ((strlen(XATTR_NAME_POSIX_ACL_DEFAULT) == xattr_len)
	     && (strncmp(XATTR_NAME_POSIX_ACL_DEFAULT, xattr, xattr_len) == 0))
		return 1;
	return 0;
}