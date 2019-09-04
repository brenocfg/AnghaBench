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
struct inode {int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  nfs_clear_inode (struct inode*) ; 
 int /*<<< orphan*/  nfs_inode_return_delegation_noreclaim (struct inode*) ; 
 int /*<<< orphan*/  pnfs_destroy_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_return_layout (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_evict_inode(struct inode *inode)
{
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	/* If we are holding a delegation, return it! */
	nfs_inode_return_delegation_noreclaim(inode);
	/* Note that above delegreturn would trigger pnfs return-on-close */
	pnfs_return_layout(inode);
	pnfs_destroy_layout(NFS_I(inode));
	/* First call standard NFS clear_inode() code */
	nfs_clear_inode(inode);
}