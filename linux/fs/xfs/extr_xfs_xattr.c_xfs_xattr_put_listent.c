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
struct xfs_attr_list_context {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  SGI_ACL_DEFAULT ; 
 int SGI_ACL_DEFAULT_SIZE ; 
 int /*<<< orphan*/  SGI_ACL_FILE ; 
 int SGI_ACL_FILE_SIZE ; 
 unsigned char* XATTR_POSIX_ACL_ACCESS ; 
 unsigned char* XATTR_POSIX_ACL_DEFAULT ; 
 char* XATTR_SECURITY_PREFIX ; 
 int XATTR_SECURITY_PREFIX_LEN ; 
 char* XATTR_SYSTEM_PREFIX ; 
 int XATTR_SYSTEM_PREFIX_LEN ; 
 char* XATTR_TRUSTED_PREFIX ; 
 int XATTR_TRUSTED_PREFIX_LEN ; 
 char* XATTR_USER_PREFIX ; 
 int XATTR_USER_PREFIX_LEN ; 
 int XFS_ATTR_ROOT ; 
 int XFS_ATTR_SECURE ; 
 int /*<<< orphan*/  __xfs_xattr_put_listent (struct xfs_attr_list_context*,char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int strlen (unsigned char*) ; 
 scalar_t__ strncmp (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xfs_xattr_put_listent(
	struct xfs_attr_list_context *context,
	int		flags,
	unsigned char	*name,
	int		namelen,
	int		valuelen)
{
	char *prefix;
	int prefix_len;

	ASSERT(context->count >= 0);

	if (flags & XFS_ATTR_ROOT) {
#ifdef CONFIG_XFS_POSIX_ACL
		if (namelen == SGI_ACL_FILE_SIZE &&
		    strncmp(name, SGI_ACL_FILE,
			    SGI_ACL_FILE_SIZE) == 0) {
			__xfs_xattr_put_listent(
					context, XATTR_SYSTEM_PREFIX,
					XATTR_SYSTEM_PREFIX_LEN,
					XATTR_POSIX_ACL_ACCESS,
					strlen(XATTR_POSIX_ACL_ACCESS));
		} else if (namelen == SGI_ACL_DEFAULT_SIZE &&
			 strncmp(name, SGI_ACL_DEFAULT,
				 SGI_ACL_DEFAULT_SIZE) == 0) {
			__xfs_xattr_put_listent(
					context, XATTR_SYSTEM_PREFIX,
					XATTR_SYSTEM_PREFIX_LEN,
					XATTR_POSIX_ACL_DEFAULT,
					strlen(XATTR_POSIX_ACL_DEFAULT));
		}
#endif

		/*
		 * Only show root namespace entries if we are actually allowed to
		 * see them.
		 */
		if (!capable(CAP_SYS_ADMIN))
			return;

		prefix = XATTR_TRUSTED_PREFIX;
		prefix_len = XATTR_TRUSTED_PREFIX_LEN;
	} else if (flags & XFS_ATTR_SECURE) {
		prefix = XATTR_SECURITY_PREFIX;
		prefix_len = XATTR_SECURITY_PREFIX_LEN;
	} else {
		prefix = XATTR_USER_PREFIX;
		prefix_len = XATTR_USER_PREFIX_LEN;
	}

	__xfs_xattr_put_listent(context, prefix, prefix_len, name,
				namelen);
	return;
}