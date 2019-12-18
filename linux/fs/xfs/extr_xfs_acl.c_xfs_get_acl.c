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
struct xfs_acl {int dummy; } ;
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int ATTR_ALLOC ; 
 int ATTR_ROOT ; 
 int /*<<< orphan*/  BUG () ; 
 int ENOATTR ; 
 struct posix_acl* ERR_PTR (int) ; 
 unsigned char* SGI_ACL_DEFAULT ; 
 unsigned char* SGI_ACL_FILE ; 
 int /*<<< orphan*/  XFS_ACL_MAX_ENTRIES (int /*<<< orphan*/ ) ; 
 int XFS_ACL_MAX_SIZE (int /*<<< orphan*/ ) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_acl*) ; 
 int /*<<< orphan*/  trace_xfs_get_acl (struct xfs_inode*) ; 
 struct posix_acl* xfs_acl_from_disk (struct xfs_acl*,int,int /*<<< orphan*/ ) ; 
 int xfs_attr_get (struct xfs_inode*,unsigned char*,unsigned char**,int*,int) ; 

struct posix_acl *
xfs_get_acl(struct inode *inode, int type)
{
	struct xfs_inode *ip = XFS_I(inode);
	struct posix_acl *acl = NULL;
	struct xfs_acl *xfs_acl = NULL;
	unsigned char *ea_name;
	int error;
	int len;

	trace_xfs_get_acl(ip);

	switch (type) {
	case ACL_TYPE_ACCESS:
		ea_name = SGI_ACL_FILE;
		break;
	case ACL_TYPE_DEFAULT:
		ea_name = SGI_ACL_DEFAULT;
		break;
	default:
		BUG();
	}

	/*
	 * If we have a cached ACLs value just return it, not need to
	 * go out to the disk.
	 */
	len = XFS_ACL_MAX_SIZE(ip->i_mount);
	error = xfs_attr_get(ip, ea_name, (unsigned char **)&xfs_acl, &len,
				ATTR_ALLOC | ATTR_ROOT);
	if (error) {
		/*
		 * If the attribute doesn't exist make sure we have a negative
		 * cache entry, for any other error assume it is transient.
		 */
		if (error != -ENOATTR)
			acl = ERR_PTR(error);
	} else  {
		acl = xfs_acl_from_disk(xfs_acl, len,
					XFS_ACL_MAX_ENTRIES(ip->i_mount));
		kmem_free(xfs_acl);
	}
	return acl;
}