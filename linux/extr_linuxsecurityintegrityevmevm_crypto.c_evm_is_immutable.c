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
struct integrity_iint_cache {int flags; } ;
struct inode {int dummy; } ;
struct evm_ima_xattr_data {scalar_t__ type; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int EVM_IMMUTABLE_DIGSIG ; 
 scalar_t__ EVM_XATTR_PORTABLE_DIGSIG ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  XATTR_NAME_EVM ; 
 struct integrity_iint_cache* integrity_iint_find (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct evm_ima_xattr_data const*) ; 
 int vfs_getxattr_alloc (struct dentry*,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evm_is_immutable(struct dentry *dentry, struct inode *inode)
{
	const struct evm_ima_xattr_data *xattr_data = NULL;
	struct integrity_iint_cache *iint;
	int rc = 0;

	iint = integrity_iint_find(inode);
	if (iint && (iint->flags & EVM_IMMUTABLE_DIGSIG))
		return 1;

	/* Do this the hard way */
	rc = vfs_getxattr_alloc(dentry, XATTR_NAME_EVM, (char **)&xattr_data, 0,
				GFP_NOFS);
	if (rc <= 0) {
		if (rc == -ENODATA)
			return 0;
		return rc;
	}
	if (xattr_data->type == EVM_XATTR_PORTABLE_DIGSIG)
		rc = 1;
	else
		rc = 0;

	kfree(xattr_data);
	return rc;
}