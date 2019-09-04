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
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRIVATE (int /*<<< orphan*/ ) ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int evm_inode_setattr (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  inode_setattr ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_setattr(struct dentry *dentry, struct iattr *attr)
{
	int ret;

	if (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		return 0;
	ret = call_int_hook(inode_setattr, 0, dentry, attr);
	if (ret)
		return ret;
	return evm_inode_setattr(dentry, attr);
}