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
struct evm_ima_xattr_data {scalar_t__ type; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EVM_IMA_XATTR_DIGSIG ; 
 scalar_t__ IMA_XATTR_LAST ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int ima_protect_xattr (struct dentry*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  ima_reset_appraise_flags (int /*<<< orphan*/ ,int) ; 

int ima_inode_setxattr(struct dentry *dentry, const char *xattr_name,
		       const void *xattr_value, size_t xattr_value_len)
{
	const struct evm_ima_xattr_data *xvalue = xattr_value;
	int result;

	result = ima_protect_xattr(dentry, xattr_name, xattr_value,
				   xattr_value_len);
	if (result == 1) {
		if (!xattr_value_len || (xvalue->type >= IMA_XATTR_LAST))
			return -EINVAL;
		ima_reset_appraise_flags(d_backing_inode(dentry),
			xvalue->type == EVM_IMA_XATTR_DIGSIG);
		result = 0;
	}
	return result;
}