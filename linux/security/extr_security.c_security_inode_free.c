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
struct rcu_head {int dummy; } ;
struct inode {scalar_t__ i_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  inode_free_by_rcu ; 
 int /*<<< orphan*/  inode_free_security ; 
 int /*<<< orphan*/  integrity_inode_free (struct inode*) ; 

void security_inode_free(struct inode *inode)
{
	integrity_inode_free(inode);
	call_void_hook(inode_free_security, inode);
	/*
	 * The inode may still be referenced in a path walk and
	 * a call to security_inode_permission() can be made
	 * after inode_free_security() is called. Ideally, the VFS
	 * wouldn't do this, but fixing that is a much harder
	 * job. For now, simply free the i_security via RCU, and
	 * leave the current inode->i_security pointer intact.
	 * The inode will be freed after the RCU grace period too.
	 */
	if (inode->i_security)
		call_rcu((struct rcu_head *)inode->i_security,
				inode_free_by_rcu);
}