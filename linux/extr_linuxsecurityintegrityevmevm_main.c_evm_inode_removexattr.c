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
 int EVM_ALLOW_METADATA_WRITES ; 
 int evm_initialized ; 
 int evm_protect_xattr (struct dentry*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int evm_inode_removexattr(struct dentry *dentry, const char *xattr_name)
{
	/* Policy permits modification of the protected xattrs even though
	 * there's no HMAC key loaded
	 */
	if (evm_initialized & EVM_ALLOW_METADATA_WRITES)
		return 0;

	return evm_protect_xattr(dentry, xattr_name, NULL, 0);
}