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
 int /*<<< orphan*/  IS_PRIVATE (int /*<<< orphan*/ ) ; 
 int call_int_hook (int /*<<< orphan*/ ,int,struct dentry*,char const*,void const*,size_t,int) ; 
 int cap_inode_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int evm_inode_setxattr (struct dentry*,char const*,void const*,size_t) ; 
 int ima_inode_setxattr (struct dentry*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  inode_setxattr ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_setxattr(struct dentry *dentry, const char *name,
			    const void *value, size_t size, int flags)
{
	int ret;

	if (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		return 0;
	/*
	 * SELinux and Smack integrate the cap call,
	 * so assume that all LSMs supplying this call do so.
	 */
	ret = call_int_hook(inode_setxattr, 1, dentry, name, value, size,
				flags);

	if (ret == 1)
		ret = cap_inode_setxattr(dentry, name, value, size, flags);
	if (ret)
		return ret;
	ret = ima_inode_setxattr(dentry, name, value, size);
	if (ret)
		return ret;
	return evm_inode_setxattr(dentry, name, value, size);
}