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
struct inode {int i_state; int /*<<< orphan*/  i_lock; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int I_OVL_INUSE ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool ovl_inuse_trylock(struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	bool locked = false;

	spin_lock(&inode->i_lock);
	if (!(inode->i_state & I_OVL_INUSE)) {
		inode->i_state |= I_OVL_INUSE;
		locked = true;
	}
	spin_unlock(&inode->i_lock);

	return locked;
}