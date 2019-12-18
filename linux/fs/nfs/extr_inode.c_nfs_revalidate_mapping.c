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
struct address_space {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_DATA_INVAL_DEFER ; 
 int /*<<< orphan*/  NFS_INO_INVALIDATING ; 
 int NFS_INO_INVALID_DATA ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int __nfs_revalidate_inode (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,unsigned long*) ; 
 int nfs_invalidate_mapping (struct inode*,struct address_space*) ; 
 scalar_t__ nfs_mapping_need_revalidate_inode (struct inode*) ; 
 int /*<<< orphan*/  nfs_wait_bit_killable ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  trace_nfs_invalidate_mapping_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_nfs_invalidate_mapping_exit (struct inode*,int) ; 
 int wait_on_bit_action (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (unsigned long*,int /*<<< orphan*/ ) ; 

int nfs_revalidate_mapping(struct inode *inode,
		struct address_space *mapping)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	unsigned long *bitlock = &nfsi->flags;
	int ret = 0;

	/* swapfiles are not supposed to be shared. */
	if (IS_SWAPFILE(inode))
		goto out;

	if (nfs_mapping_need_revalidate_inode(inode)) {
		ret = __nfs_revalidate_inode(NFS_SERVER(inode), inode);
		if (ret < 0)
			goto out;
	}

	/*
	 * We must clear NFS_INO_INVALID_DATA first to ensure that
	 * invalidations that come in while we're shooting down the mappings
	 * are respected. But, that leaves a race window where one revalidator
	 * can clear the flag, and then another checks it before the mapping
	 * gets invalidated. Fix that by serializing access to this part of
	 * the function.
	 *
	 * At the same time, we need to allow other tasks to see whether we
	 * might be in the middle of invalidating the pages, so we only set
	 * the bit lock here if it looks like we're going to be doing that.
	 */
	for (;;) {
		ret = wait_on_bit_action(bitlock, NFS_INO_INVALIDATING,
					 nfs_wait_bit_killable, TASK_KILLABLE);
		if (ret)
			goto out;
		spin_lock(&inode->i_lock);
		if (test_bit(NFS_INO_INVALIDATING, bitlock)) {
			spin_unlock(&inode->i_lock);
			continue;
		}
		if (nfsi->cache_validity & NFS_INO_INVALID_DATA)
			break;
		spin_unlock(&inode->i_lock);
		goto out;
	}

	set_bit(NFS_INO_INVALIDATING, bitlock);
	smp_wmb();
	nfsi->cache_validity &= ~(NFS_INO_INVALID_DATA|
			NFS_INO_DATA_INVAL_DEFER);
	spin_unlock(&inode->i_lock);
	trace_nfs_invalidate_mapping_enter(inode);
	ret = nfs_invalidate_mapping(inode, mapping);
	trace_nfs_invalidate_mapping_exit(inode, ret);

	clear_bit_unlock(NFS_INO_INVALIDATING, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, NFS_INO_INVALIDATING);
out:
	return ret;
}