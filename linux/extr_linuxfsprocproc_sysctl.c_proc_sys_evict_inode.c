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
struct inode {int dummy; } ;
struct ctl_table_header {int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysctl_inodes; } ;

/* Variables and functions */
 TYPE_1__* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct ctl_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 

void proc_sys_evict_inode(struct inode *inode, struct ctl_table_header *head)
{
	spin_lock(&sysctl_lock);
	hlist_del_init_rcu(&PROC_I(inode)->sysctl_inodes);
	if (!--head->count)
		kfree_rcu(head, rcu);
	spin_unlock(&sysctl_lock);
}