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

/* Variables and functions */
 int I_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __I_NEW ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lockdep_annotate_inode_mutex_key (struct inode*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int*,int /*<<< orphan*/ ) ; 

void discard_new_inode(struct inode *inode)
{
	lockdep_annotate_inode_mutex_key(inode);
	spin_lock(&inode->i_lock);
	WARN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unlock(&inode->i_lock);
	iput(inode);
}