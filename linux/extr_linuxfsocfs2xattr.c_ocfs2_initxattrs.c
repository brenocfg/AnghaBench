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
struct xattr {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_XATTR_INDEX_SECURITY ; 
 int /*<<< orphan*/  XATTR_CREATE ; 
 int ocfs2_xattr_set (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_initxattrs(struct inode *inode, const struct xattr *xattr_array,
		     void *fs_info)
{
	const struct xattr *xattr;
	int err = 0;

	for (xattr = xattr_array; xattr->name != NULL; xattr++) {
		err = ocfs2_xattr_set(inode, OCFS2_XATTR_INDEX_SECURITY,
				      xattr->name, xattr->value,
				      xattr->value_len, XATTR_CREATE);
		if (err)
			break;
	}
	return err;
}