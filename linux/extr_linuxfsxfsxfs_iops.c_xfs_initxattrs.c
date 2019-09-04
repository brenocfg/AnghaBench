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
struct xfs_inode {int dummy; } ;
struct xattr {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SECURE ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int xfs_attr_set (struct xfs_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_initxattrs(
	struct inode		*inode,
	const struct xattr	*xattr_array,
	void			*fs_info)
{
	const struct xattr	*xattr;
	struct xfs_inode	*ip = XFS_I(inode);
	int			error = 0;

	for (xattr = xattr_array; xattr->name != NULL; xattr++) {
		error = xfs_attr_set(ip, xattr->name, xattr->value,
				      xattr->value_len, ATTR_SECURE);
		if (error < 0)
			break;
	}
	return error;
}