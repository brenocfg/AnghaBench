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
struct nfs_delegation {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_do_return_delegation (struct inode*,struct nfs_delegation*,int) ; 
 struct nfs_delegation* nfs_inode_detach_delegation (struct inode*) ; 

void nfs_inode_return_delegation_noreclaim(struct inode *inode)
{
	struct nfs_delegation *delegation;

	delegation = nfs_inode_detach_delegation(inode);
	if (delegation != NULL)
		nfs_do_return_delegation(inode, delegation, 1);
}