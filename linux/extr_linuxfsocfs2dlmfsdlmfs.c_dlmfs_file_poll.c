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
struct file {int dummy; } ;
struct TYPE_2__ {int l_flags; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_event; } ;
struct dlmfs_inode_private {TYPE_1__ ip_lockres; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int USER_LOCK_BLOCKED ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dlmfs_file_poll(struct file *file, poll_table *wait)
{
	__poll_t event = 0;
	struct inode *inode = file_inode(file);
	struct dlmfs_inode_private *ip = DLMFS_I(inode);

	poll_wait(file, &ip->ip_lockres.l_event, wait);

	spin_lock(&ip->ip_lockres.l_lock);
	if (ip->ip_lockres.l_flags & USER_LOCK_BLOCKED)
		event = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&ip->ip_lockres.l_lock);

	return event;
}