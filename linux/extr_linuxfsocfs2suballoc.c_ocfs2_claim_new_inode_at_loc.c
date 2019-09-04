#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_suballoc_result {scalar_t__ sr_blkno; int sr_bits; scalar_t__ sr_bg_blkno; int /*<<< orphan*/  sr_bit_offset; int /*<<< orphan*/  sr_bg_stable_blkno; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_chain; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_bits_given; TYPE_2__* ac_inode; TYPE_3__* ac_bh; struct ocfs2_suballoc_result* ac_find_loc_priv; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  bg_allocs; } ;
struct TYPE_12__ {TYPE_1__ alloc_stats; } ;
struct TYPE_11__ {scalar_t__ b_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_8__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_alloc_dinode_update_counts (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int ocfs2_block_group_set_bits (int /*<<< orphan*/ *,TYPE_2__*,struct ocfs2_group_desc*,struct buffer_head*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_read_group_descriptor (TYPE_2__*,struct ocfs2_dinode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_rollback_alloc_dinode_counts (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_save_inode_ac_group (struct inode*,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  trace_ocfs2_claim_new_inode_at_loc (unsigned long long,int) ; 

int ocfs2_claim_new_inode_at_loc(handle_t *handle,
				 struct inode *dir,
				 struct ocfs2_alloc_context *ac,
				 u64 *suballoc_loc,
				 u16 *suballoc_bit,
				 u64 di_blkno)
{
	int ret;
	u16 chain;
	struct ocfs2_suballoc_result *res = ac->ac_find_loc_priv;
	struct buffer_head *bg_bh = NULL;
	struct ocfs2_group_desc *bg;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *) ac->ac_bh->b_data;

	/*
	 * Since di_blkno is being passed back in, we check for any
	 * inconsistencies which may have happened between
	 * calls. These are code bugs as di_blkno is not expected to
	 * change once returned from ocfs2_find_new_inode_loc()
	 */
	BUG_ON(res->sr_blkno != di_blkno);

	ret = ocfs2_read_group_descriptor(ac->ac_inode, di,
					  res->sr_bg_stable_blkno, &bg_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	bg = (struct ocfs2_group_desc *) bg_bh->b_data;
	chain = le16_to_cpu(bg->bg_chain);

	ret = ocfs2_alloc_dinode_update_counts(ac->ac_inode, handle,
					       ac->ac_bh, res->sr_bits,
					       chain);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_block_group_set_bits(handle,
					 ac->ac_inode,
					 bg,
					 bg_bh,
					 res->sr_bit_offset,
					 res->sr_bits);
	if (ret < 0) {
		ocfs2_rollback_alloc_dinode_counts(ac->ac_inode,
					       ac->ac_bh, res->sr_bits, chain);
		mlog_errno(ret);
		goto out;
	}

	trace_ocfs2_claim_new_inode_at_loc((unsigned long long)di_blkno,
					   res->sr_bits);

	atomic_inc(&OCFS2_SB(ac->ac_inode->i_sb)->alloc_stats.bg_allocs);

	BUG_ON(res->sr_bits != 1);

	*suballoc_loc = res->sr_bg_blkno;
	*suballoc_bit = res->sr_bit_offset;
	ac->ac_bits_given++;
	ocfs2_save_inode_ac_group(dir, ac);

out:
	brelse(bg_bh);

	return ret;
}