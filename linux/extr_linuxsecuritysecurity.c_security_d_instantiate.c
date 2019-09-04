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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  d_instantiate ; 
 scalar_t__ unlikely (int) ; 

void security_d_instantiate(struct dentry *dentry, struct inode *inode)
{
	if (unlikely(inode && IS_PRIVATE(inode)))
		return;
	call_void_hook(d_instantiate, dentry, inode);
}