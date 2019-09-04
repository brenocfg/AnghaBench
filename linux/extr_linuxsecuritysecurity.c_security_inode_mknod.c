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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_mknod ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
{
	if (unlikely(IS_PRIVATE(dir)))
		return 0;
	return call_int_hook(inode_mknod, 0, dir, dentry, mode, dev);
}