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
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct dentry*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  evm_inode_post_setxattr (struct dentry*,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  inode_post_setxattr ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void security_inode_post_setxattr(struct dentry *dentry, const char *name,
				  const void *value, size_t size, int flags)
{
	if (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		return;
	call_void_hook(inode_post_setxattr, dentry, name, value, size, flags);
	evm_inode_post_setxattr(dentry, name, value, size);
}