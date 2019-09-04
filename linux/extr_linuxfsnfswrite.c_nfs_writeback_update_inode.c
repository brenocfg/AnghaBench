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
struct nfs_fattr {int dummy; } ;
struct nfs_pgio_header {struct inode* inode; struct nfs_fattr fattr; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_post_op_update_inode_force_wcc_locked (struct inode*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_writeback_check_extend (struct nfs_pgio_header*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_writeback_update_inode(struct nfs_pgio_header *hdr)
{
	struct nfs_fattr *fattr = &hdr->fattr;
	struct inode *inode = hdr->inode;

	spin_lock(&inode->i_lock);
	nfs_writeback_check_extend(hdr, fattr);
	nfs_post_op_update_inode_force_wcc_locked(inode, fattr);
	spin_unlock(&inode->i_lock);
}