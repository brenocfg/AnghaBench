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
struct inode {int dummy; } ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 int __nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 
 int /*<<< orphan*/  nfs_need_revalidate_inode (struct inode*) ; 

int nfs_revalidate_inode(struct nfs_server *server, struct inode *inode)
{
	if (!nfs_need_revalidate_inode(inode))
		return NFS_STALE(inode) ? -ESTALE : 0;
	return __nfs_revalidate_inode(server, inode);
}