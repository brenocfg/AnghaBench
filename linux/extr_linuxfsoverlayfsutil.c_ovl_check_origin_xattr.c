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
 int /*<<< orphan*/  OVL_XATTR_ORIGIN ; 
 int vfs_getxattr (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool ovl_check_origin_xattr(struct dentry *dentry)
{
	int res;

	res = vfs_getxattr(dentry, OVL_XATTR_ORIGIN, NULL, 0);

	/* Zero size value means "copied up but origin unknown" */
	if (res >= 0)
		return true;

	return false;
}