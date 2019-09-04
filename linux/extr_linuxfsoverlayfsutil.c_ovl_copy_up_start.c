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
struct ovl_inode {int /*<<< orphan*/  lock; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct ovl_inode* OVL_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ovl_already_copied_up_locked (struct dentry*,int) ; 

int ovl_copy_up_start(struct dentry *dentry, int flags)
{
	struct ovl_inode *oi = OVL_I(d_inode(dentry));
	int err;

	err = mutex_lock_interruptible(&oi->lock);
	if (!err && ovl_already_copied_up_locked(dentry, flags)) {
		err = 1; /* Already copied up */
		mutex_unlock(&oi->lock);
	}

	return err;
}