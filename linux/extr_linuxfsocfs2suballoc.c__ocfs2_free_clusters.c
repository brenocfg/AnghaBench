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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int _ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,scalar_t__,unsigned int,void (*) (unsigned int,unsigned long*)) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_block_to_cluster_group (struct inode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_local_alloc_seen_free_bits (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_ocfs2_free_clusters (unsigned long long,unsigned long long,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int _ocfs2_free_clusters(handle_t *handle,
				struct inode *bitmap_inode,
				struct buffer_head *bitmap_bh,
				u64 start_blk,
				unsigned int num_clusters,
				void (*undo_fn)(unsigned int bit,
						unsigned long *bitmap))
{
	int status;
	u16 bg_start_bit;
	u64 bg_blkno;

	/* You can't ever have a contiguous set of clusters
	 * bigger than a block group bitmap so we never have to worry
	 * about looping on them.
	 * This is expensive. We can safely remove once this stuff has
	 * gotten tested really well. */
	BUG_ON(start_blk != ocfs2_clusters_to_blocks(bitmap_inode->i_sb,
				ocfs2_blocks_to_clusters(bitmap_inode->i_sb,
							 start_blk)));


	ocfs2_block_to_cluster_group(bitmap_inode, start_blk, &bg_blkno,
				     &bg_start_bit);

	trace_ocfs2_free_clusters((unsigned long long)bg_blkno,
			(unsigned long long)start_blk,
			bg_start_bit, num_clusters);

	status = _ocfs2_free_suballoc_bits(handle, bitmap_inode, bitmap_bh,
					   bg_start_bit, bg_blkno,
					   num_clusters, undo_fn);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	ocfs2_local_alloc_seen_free_bits(OCFS2_SB(bitmap_inode->i_sb),
					 num_clusters);

out:
	if (status)
		mlog_errno(status);
	return status;
}