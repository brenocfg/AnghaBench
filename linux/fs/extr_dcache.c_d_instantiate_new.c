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
struct inode {int i_state; int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_alias; } ;
struct dentry {TYPE_1__ d_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CREATING ; 
 int I_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __I_NEW ; 
 int /*<<< orphan*/  __d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_annotate_inode_mutex_key (struct inode*) ; 
 int /*<<< orphan*/  security_d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int*,int /*<<< orphan*/ ) ; 

void d_instantiate_new(struct dentry *entry, struct inode *inode)
{
	BUG_ON(!hlist_unhashed(&entry->d_u.d_alias));
	BUG_ON(!inode);
	lockdep_annotate_inode_mutex_key(inode);
	security_d_instantiate(entry, inode);
	spin_lock(&inode->i_lock);
	__d_instantiate(entry, inode);
	WARN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW & ~I_CREATING;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unlock(&inode->i_lock);
}