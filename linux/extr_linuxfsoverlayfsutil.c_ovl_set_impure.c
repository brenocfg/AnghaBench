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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_IMPURE ; 
 int /*<<< orphan*/  OVL_XATTR_IMPURE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int ovl_check_setxattr (struct dentry*,struct dentry*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_set_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ovl_set_impure(struct dentry *dentry, struct dentry *upperdentry)
{
	int err;

	if (ovl_test_flag(OVL_IMPURE, d_inode(dentry)))
		return 0;

	/*
	 * Do not fail when upper doesn't support xattrs.
	 * Upper inodes won't have origin nor redirect xattr anyway.
	 */
	err = ovl_check_setxattr(dentry, upperdentry, OVL_XATTR_IMPURE,
				 "y", 1, 0);
	if (!err)
		ovl_set_flag(OVL_IMPURE, d_inode(dentry));

	return err;
}