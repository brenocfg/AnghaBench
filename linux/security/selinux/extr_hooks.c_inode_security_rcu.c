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
struct inode_security_struct {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode_security_struct* ERR_PTR (int) ; 
 int __inode_security_revalidate (struct inode*,int /*<<< orphan*/ *,int) ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 

__attribute__((used)) static struct inode_security_struct *inode_security_rcu(struct inode *inode, bool rcu)
{
	int error;

	error = __inode_security_revalidate(inode, NULL, !rcu);
	if (error)
		return ERR_PTR(error);
	return selinux_inode(inode);
}