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
struct nfs_server {int dummy; } ;
struct nfs_inode {int dummy; } ;
struct nfs_delegation {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 struct nfs_delegation* nfs_detach_delegation (struct nfs_inode*,struct nfs_delegation*,struct nfs_server*) ; 
 struct nfs_delegation* nfs_start_delegation_return (struct nfs_inode*) ; 

__attribute__((used)) static struct nfs_delegation *
nfs_inode_detach_delegation(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs_delegation *delegation;

	delegation = nfs_start_delegation_return(nfsi);
	if (delegation == NULL)
		return NULL;
	return nfs_detach_delegation(nfsi, delegation, server);
}