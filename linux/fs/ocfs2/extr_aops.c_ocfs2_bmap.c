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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  INODE_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_is_refcount_inode (struct inode*) ; 
 int /*<<< orphan*/  trace_ocfs2_bmap (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sector_t ocfs2_bmap(struct address_space *mapping, sector_t block)
{
	sector_t status;
	u64 p_blkno = 0;
	int err = 0;
	struct inode *inode = mapping->host;

	trace_ocfs2_bmap((unsigned long long)OCFS2_I(inode)->ip_blkno,
			 (unsigned long long)block);

	/*
	 * The swap code (ab-)uses ->bmap to get a block mapping and then
	 * bypasseѕ the file system for actual I/O.  We really can't allow
	 * that on refcounted inodes, so we have to skip out here.  And yes,
	 * 0 is the magic code for a bmap error..
	 */
	if (ocfs2_is_refcount_inode(inode))
		return 0;

	/* We don't need to lock journal system files, since they aren't
	 * accessed concurrently from multiple nodes.
	 */
	if (!INODE_JOURNAL(inode)) {
		err = ocfs2_inode_lock(inode, NULL, 0);
		if (err) {
			if (err != -ENOENT)
				mlog_errno(err);
			goto bail;
		}
		down_read(&OCFS2_I(inode)->ip_alloc_sem);
	}

	if (!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL))
		err = ocfs2_extent_map_get_blocks(inode, block, &p_blkno, NULL,
						  NULL);

	if (!INODE_JOURNAL(inode)) {
		up_read(&OCFS2_I(inode)->ip_alloc_sem);
		ocfs2_inode_unlock(inode, 0);
	}

	if (err) {
		mlog(ML_ERROR, "get_blocks() failed, block = %llu\n",
		     (unsigned long long)block);
		mlog_errno(err);
		goto bail;
	}

bail:
	status = err ? 0 : p_blkno;

	return status;
}