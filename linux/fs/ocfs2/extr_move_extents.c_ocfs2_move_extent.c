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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {struct inode* osb_tl_inode; } ;
struct ocfs2_refcount_tree {int dummy; } ;
struct ocfs2_move_extents_context {int /*<<< orphan*/ * meta_ac; struct inode* inode; int /*<<< orphan*/  et; int /*<<< orphan*/  refcount_loc; TYPE_1__* range; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_chain; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  me_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_EXT_REFCOUNTED ; 
 scalar_t__ OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_move_extent (int /*<<< orphan*/ *,struct ocfs2_move_extents_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_alloc_dinode_update_counts (struct inode*,int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_block_group_set_bits (int /*<<< orphan*/ *,struct inode*,struct ocfs2_group_desc*,struct buffer_head*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_cow_sync_writeback (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_find_victim_alloc_group (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (int /*<<< orphan*/ *) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_is_refcount_inode (struct inode*) ; 
 int ocfs2_lock_meta_allocator_move_extents (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int,int*) ; 
 int ocfs2_lock_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ,int,struct ocfs2_refcount_tree**,int /*<<< orphan*/ *) ; 
 int ocfs2_prepare_refcount_change_for_del (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ocfs2_probe_alloc_group (struct inode*,struct buffer_head*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_rollback_alloc_dinode_counts (struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 

__attribute__((used)) static int ocfs2_move_extent(struct ocfs2_move_extents_context *context,
			     u32 cpos, u32 phys_cpos, u32 *new_phys_cpos,
			     u32 len, int ext_flags)
{
	int ret, credits = 0, extra_blocks = 0, goal_bit = 0;
	handle_t *handle;
	struct inode *inode = context->inode;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct inode *tl_inode = osb->osb_tl_inode;
	struct inode *gb_inode = NULL;
	struct buffer_head *gb_bh = NULL;
	struct buffer_head *gd_bh = NULL;
	struct ocfs2_group_desc *gd;
	struct ocfs2_refcount_tree *ref_tree = NULL;
	u32 move_max_hop = ocfs2_blocks_to_clusters(inode->i_sb,
						    context->range->me_threshold);
	u64 phys_blkno, new_phys_blkno;

	phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);

	if ((ext_flags & OCFS2_EXT_REFCOUNTED) && len) {
		BUG_ON(!ocfs2_is_refcount_inode(inode));
		BUG_ON(!context->refcount_loc);

		ret = ocfs2_lock_refcount_tree(osb, context->refcount_loc, 1,
					       &ref_tree, NULL);
		if (ret) {
			mlog_errno(ret);
			return ret;
		}

		ret = ocfs2_prepare_refcount_change_for_del(inode,
							context->refcount_loc,
							phys_blkno,
							len,
							&credits,
							&extra_blocks);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	ret = ocfs2_lock_meta_allocator_move_extents(inode, &context->et,
						len, 1,
						&context->meta_ac,
						extra_blocks, &credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * need to count 2 extra credits for global_bitmap inode and
	 * group descriptor.
	 */
	credits += OCFS2_INODE_UPDATE_CREDITS + 1;

	/*
	 * ocfs2_move_extent() didn't reserve any clusters in lock_allocators()
	 * logic, while we still need to lock the global_bitmap.
	 */
	gb_inode = ocfs2_get_system_file_inode(osb, GLOBAL_BITMAP_SYSTEM_INODE,
					       OCFS2_INVALID_SLOT);
	if (!gb_inode) {
		mlog(ML_ERROR, "unable to get global_bitmap inode\n");
		ret = -EIO;
		goto out;
	}

	inode_lock(gb_inode);

	ret = ocfs2_inode_lock(gb_inode, &gb_bh, 1);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock_gb_mutex;
	}

	inode_lock(tl_inode);

	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out_unlock_tl_inode;
	}

	new_phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, *new_phys_cpos);
	ret = ocfs2_find_victim_alloc_group(inode, new_phys_blkno,
					    GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT,
					    &goal_bit, &gd_bh);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	/*
	 * probe the victim cluster group to find a proper
	 * region to fit wanted movement, it even will perfrom
	 * a best-effort attempt by compromising to a threshold
	 * around the goal.
	 */
	ocfs2_probe_alloc_group(inode, gd_bh, &goal_bit, len, move_max_hop,
				new_phys_cpos);
	if (!*new_phys_cpos) {
		ret = -ENOSPC;
		goto out_commit;
	}

	ret = __ocfs2_move_extent(handle, context, cpos, len, phys_cpos,
				  *new_phys_cpos, ext_flags);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	gd = (struct ocfs2_group_desc *)gd_bh->b_data;
	ret = ocfs2_alloc_dinode_update_counts(gb_inode, handle, gb_bh, len,
					       le16_to_cpu(gd->bg_chain));
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = ocfs2_block_group_set_bits(handle, gb_inode, gd, gd_bh,
					 goal_bit, len);
	if (ret) {
		ocfs2_rollback_alloc_dinode_counts(gb_inode, gb_bh, len,
					       le16_to_cpu(gd->bg_chain));
		mlog_errno(ret);
	}

	/*
	 * Here we should write the new page out first if we are
	 * in write-back mode.
	 */
	ret = ocfs2_cow_sync_writeback(inode->i_sb, context->inode, cpos, len);
	if (ret)
		mlog_errno(ret);

out_commit:
	ocfs2_commit_trans(osb, handle);
	brelse(gd_bh);

out_unlock_tl_inode:
	inode_unlock(tl_inode);

	ocfs2_inode_unlock(gb_inode, 1);
out_unlock_gb_mutex:
	inode_unlock(gb_inode);
	brelse(gb_bh);
	iput(gb_inode);

out:
	if (context->meta_ac) {
		ocfs2_free_alloc_context(context->meta_ac);
		context->meta_ac = NULL;
	}

	if (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	return ret;
}