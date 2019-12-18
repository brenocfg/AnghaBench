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
struct xfs_inode {int /*<<< orphan*/  i_mount; } ;
struct xfs_acl_entry {int dummy; } ;
struct xfs_acl {int dummy; } ;
struct posix_acl {int a_count; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  ATTR_ROOT ; 
 int EACCES ; 
 int EINVAL ; 
 int ENOATTR ; 
 int ENOMEM ; 
 unsigned char* SGI_ACL_DEFAULT ; 
 unsigned char* SGI_ACL_FILE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int XFS_ACL_MAX_ENTRIES (int /*<<< orphan*/ ) ; 
 int XFS_ACL_MAX_SIZE (int /*<<< orphan*/ ) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_acl*) ; 
 struct xfs_acl* kmem_zalloc_large (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  xfs_acl_to_disk (struct xfs_acl*,struct posix_acl*) ; 
 int xfs_attr_remove (struct xfs_inode*,unsigned char*,int /*<<< orphan*/ ) ; 
 int xfs_attr_set (struct xfs_inode*,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ) ; 

int
__xfs_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	struct xfs_inode *ip = XFS_I(inode);
	unsigned char *ea_name;
	int error;

	switch (type) {
	case ACL_TYPE_ACCESS:
		ea_name = SGI_ACL_FILE;
		break;
	case ACL_TYPE_DEFAULT:
		if (!S_ISDIR(inode->i_mode))
			return acl ? -EACCES : 0;
		ea_name = SGI_ACL_DEFAULT;
		break;
	default:
		return -EINVAL;
	}

	if (acl) {
		struct xfs_acl *xfs_acl;
		int len = XFS_ACL_MAX_SIZE(ip->i_mount);

		xfs_acl = kmem_zalloc_large(len, 0);
		if (!xfs_acl)
			return -ENOMEM;

		xfs_acl_to_disk(xfs_acl, acl);

		/* subtract away the unused acl entries */
		len -= sizeof(struct xfs_acl_entry) *
			 (XFS_ACL_MAX_ENTRIES(ip->i_mount) - acl->a_count);

		error = xfs_attr_set(ip, ea_name, (unsigned char *)xfs_acl,
				len, ATTR_ROOT);

		kmem_free(xfs_acl);
	} else {
		/*
		 * A NULL ACL argument means we want to remove the ACL.
		 */
		error = xfs_attr_remove(ip, ea_name, ATTR_ROOT);

		/*
		 * If the attribute didn't exist to start with that's fine.
		 */
		if (error == -ENOATTR)
			error = 0;
	}

	if (!error)
		set_cached_acl(inode, type, acl);
	return error;
}