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
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  evm_key_loaded () ; 
 int /*<<< orphan*/  evm_protected_xattr (char const*) ; 
 int /*<<< orphan*/  evm_reset_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evm_update_evmxattr (struct dentry*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  posix_xattr_acl (char const*) ; 

void evm_inode_post_setxattr(struct dentry *dentry, const char *xattr_name,
			     const void *xattr_value, size_t xattr_value_len)
{
	if (!evm_key_loaded() || (!evm_protected_xattr(xattr_name)
				  && !posix_xattr_acl(xattr_name)))
		return;

	evm_reset_status(dentry->d_inode);

	evm_update_evmxattr(dentry, xattr_name, xattr_value, xattr_value_len);
}