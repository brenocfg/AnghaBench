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
struct inode_smack {int /*<<< orphan*/  smk_rcu; } ;
struct inode {struct inode_smack* i_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_inode_free_rcu ; 

__attribute__((used)) static void smack_inode_free_security(struct inode *inode)
{
	struct inode_smack *issp = inode->i_security;

	/*
	 * The inode may still be referenced in a path walk and
	 * a call to smack_inode_permission() can be made
	 * after smack_inode_free_security() is called.
	 * To avoid race condition free the i_security via RCU
	 * and leave the current inode->i_security pointer intact.
	 * The inode will be freed after the RCU grace period too.
	 */
	call_rcu(&issp->smk_rcu, smack_inode_free_rcu);
}