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
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_listxattr ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_listxattr(struct dentry *dentry)
{
	if (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		return 0;
	return call_int_hook(inode_listxattr, 0, dentry);
}