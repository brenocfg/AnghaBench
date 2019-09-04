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
struct evm_ima_xattr_data {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  XATTR_NAME_IMA ; 
 int vfs_getxattr_alloc (struct dentry*,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ima_read_xattr(struct dentry *dentry,
		   struct evm_ima_xattr_data **xattr_value)
{
	ssize_t ret;

	ret = vfs_getxattr_alloc(dentry, XATTR_NAME_IMA, (char **)xattr_value,
				 0, GFP_NOFS);
	if (ret == -EOPNOTSUPP)
		ret = 0;
	return ret;
}