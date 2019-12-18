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
struct nfs_inode {int dummy; } ;
struct nfs_delegation {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int nfs_end_delegation_return (struct inode*,struct nfs_delegation*,int) ; 
 struct nfs_delegation* nfs_start_delegation_return (struct nfs_inode*) ; 
 int /*<<< orphan*/  nfs_wb_all (struct inode*) ; 

int nfs4_inode_return_delegation(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_delegation *delegation;
	int err = 0;

	nfs_wb_all(inode);
	delegation = nfs_start_delegation_return(nfsi);
	if (delegation != NULL)
		err = nfs_end_delegation_return(inode, delegation, 1);
	return err;
}