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
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  evm_key_loaded () ; 
 int /*<<< orphan*/  evm_update_evmxattr (struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void evm_inode_post_setattr(struct dentry *dentry, int ia_valid)
{
	if (!evm_key_loaded())
		return;

	if (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID))
		evm_update_evmxattr(dentry, NULL, NULL, 0);
}