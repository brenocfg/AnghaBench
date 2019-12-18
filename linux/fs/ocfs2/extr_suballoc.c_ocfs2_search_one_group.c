#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_suballoc_result {int /*<<< orphan*/  sr_bits; int /*<<< orphan*/  sr_bit_offset; int /*<<< orphan*/  sr_bg_stable_blkno; int /*<<< orphan*/  sr_bg_blkno; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_chain; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {int (* ac_group_search ) (struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_suballoc_result*) ;TYPE_1__* ac_bh; scalar_t__ ac_find_loc_only; int /*<<< orphan*/  ac_max_block; struct inode* ac_inode; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_3__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_alloc_dinode_update_counts (struct inode*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_bg_discontig_fix_result (struct ocfs2_alloc_context*,struct ocfs2_group_desc*,struct ocfs2_suballoc_result*) ; 
 int ocfs2_block_group_set_bits (int /*<<< orphan*/ *,struct inode*,struct ocfs2_group_desc*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_read_group_descriptor (struct inode*,struct ocfs2_dinode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_rollback_alloc_dinode_counts (struct inode*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_suballoc_result*) ; 

__attribute__((used)) static int ocfs2_search_one_group(struct ocfs2_alloc_context *ac,
				  handle_t *handle,
				  u32 bits_wanted,
				  u32 min_bits,
				  struct ocfs2_suballoc_result *res,
				  u16 *bits_left)
{
	int ret;
	struct buffer_head *group_bh = NULL;
	struct ocfs2_group_desc *gd;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)ac->ac_bh->b_data;
	struct inode *alloc_inode = ac->ac_inode;

	ret = ocfs2_read_group_descriptor(alloc_inode, di,
					  res->sr_bg_blkno, &group_bh);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	gd = (struct ocfs2_group_desc *) group_bh->b_data;
	ret = ac->ac_group_search(alloc_inode, group_bh, bits_wanted, min_bits,
				  ac->ac_max_block, res);
	if (ret < 0) {
		if (ret != -ENOSPC)
			mlog_errno(ret);
		goto out;
	}

	if (!ret)
		ocfs2_bg_discontig_fix_result(ac, gd, res);

	/*
	 * sr_bg_blkno might have been changed by
	 * ocfs2_bg_discontig_fix_result
	 */
	res->sr_bg_stable_blkno = group_bh->b_blocknr;

	if (ac->ac_find_loc_only)
		goto out_loc_only;

	ret = ocfs2_alloc_dinode_update_counts(alloc_inode, handle, ac->ac_bh,
					       res->sr_bits,
					       le16_to_cpu(gd->bg_chain));
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_block_group_set_bits(handle, alloc_inode, gd, group_bh,
					 res->sr_bit_offset, res->sr_bits);
	if (ret < 0) {
		ocfs2_rollback_alloc_dinode_counts(alloc_inode, ac->ac_bh,
					       res->sr_bits,
					       le16_to_cpu(gd->bg_chain));
		mlog_errno(ret);
	}

out_loc_only:
	*bits_left = le16_to_cpu(gd->bg_free_bits_count);

out:
	brelse(group_bh);

	return ret;
}