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
struct nfs_inode {unsigned long flags; int cache_validity; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int ECHILD ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_INVALIDATING ; 
 int NFS_INO_INVALID_DATA ; 
 scalar_t__ nfs_mapping_need_revalidate_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

int nfs_revalidate_mapping_rcu(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	unsigned long *bitlock = &nfsi->flags;
	int ret = 0;

	if (IS_SWAPFILE(inode))
		goto out;
	if (nfs_mapping_need_revalidate_inode(inode)) {
		ret = -ECHILD;
		goto out;
	}
	spin_lock(&inode->i_lock);
	if (test_bit(NFS_INO_INVALIDATING, bitlock) ||
	    (nfsi->cache_validity & NFS_INO_INVALID_DATA))
		ret = -ECHILD;
	spin_unlock(&inode->i_lock);
out:
	return ret;
}