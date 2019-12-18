#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {int count; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; TYPE_1__ d_lockref; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_CANT_MOUNT ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unlink_inode (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void d_delete(struct dentry * dentry)
{
	struct inode *inode = dentry->d_inode;

	spin_lock(&inode->i_lock);
	spin_lock(&dentry->d_lock);
	/*
	 * Are we the only user?
	 */
	if (dentry->d_lockref.count == 1) {
		dentry->d_flags &= ~DCACHE_CANT_MOUNT;
		dentry_unlink_inode(dentry);
	} else {
		__d_drop(dentry);
		spin_unlock(&dentry->d_lock);
		spin_unlock(&inode->i_lock);
	}
}