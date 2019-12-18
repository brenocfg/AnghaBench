#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {scalar_t__ sync_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  rpcs_out; int /*<<< orphan*/  ncommit; } ;
struct nfs_inode {TYPE_1__ commit_info; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int FLUSH_SYNC ; 
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 scalar_t__ WB_SYNC_NONE ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int __nfs_commit_inode (struct inode*,int,struct writeback_control*) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mapping_tagged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	int flags = FLUSH_SYNC;
	int ret = 0;

	if (wbc->sync_mode == WB_SYNC_NONE) {
		/* no commits means nothing needs to be done */
		if (!atomic_long_read(&nfsi->commit_info.ncommit))
			goto check_requests_outstanding;

		/* Don't commit yet if this is a non-blocking flush and there
		 * are a lot of outstanding writes for this mapping.
		 */
		if (mapping_tagged(inode->i_mapping, PAGECACHE_TAG_WRITEBACK))
			goto out_mark_dirty;

		/* don't wait for the COMMIT response */
		flags = 0;
	}

	ret = __nfs_commit_inode(inode, flags, wbc);
	if (!ret) {
		if (flags & FLUSH_SYNC)
			return 0;
	} else if (atomic_long_read(&nfsi->commit_info.ncommit))
		goto out_mark_dirty;

check_requests_outstanding:
	if (!atomic_read(&nfsi->commit_info.rpcs_out))
		return ret;
out_mark_dirty:
	__mark_inode_dirty(inode, I_DIRTY_DATASYNC);
	return ret;
}