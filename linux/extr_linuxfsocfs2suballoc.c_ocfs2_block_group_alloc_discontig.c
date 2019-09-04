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
typedef  unsigned int u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_cpg; } ;
struct ocfs2_alloc_context {int ac_disable_chain_relink; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct buffer_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_bg_alloc_cleanup (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,struct inode*,struct buffer_head*) ; 
 int ocfs2_block_group_claim_bits (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,unsigned int,unsigned int*,unsigned int*) ; 
 int ocfs2_block_group_fill (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,scalar_t__,unsigned int,unsigned int,struct ocfs2_chain_list*) ; 
 int ocfs2_block_group_grow_discontig (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct ocfs2_alloc_context*,struct ocfs2_chain_list*,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_calc_bg_discontig_credits (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,unsigned int) ; 
 int ocfs2_extend_trans (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int ocfs2_find_smallest_chain (struct ocfs2_chain_list*) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_supports_discontig_bg (struct ocfs2_super*) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_ocfs2_block_group_alloc_discontig (unsigned long long,unsigned int) ; 

__attribute__((used)) static struct buffer_head *
ocfs2_block_group_alloc_discontig(handle_t *handle,
				  struct inode *alloc_inode,
				  struct ocfs2_alloc_context *ac,
				  struct ocfs2_chain_list *cl)
{
	int status;
	u32 bit_off, num_bits;
	u64 bg_blkno;
	unsigned int min_bits = le16_to_cpu(cl->cl_cpg) >> 1;
	struct buffer_head *bg_bh = NULL;
	unsigned int alloc_rec = ocfs2_find_smallest_chain(cl);
	struct ocfs2_super *osb = OCFS2_SB(alloc_inode->i_sb);

	if (!ocfs2_supports_discontig_bg(osb)) {
		status = -ENOSPC;
		goto bail;
	}

	status = ocfs2_extend_trans(handle,
				    ocfs2_calc_bg_discontig_credits(osb->sb));
	if (status) {
		mlog_errno(status);
		goto bail;
	}

	/*
	 * We're going to be grabbing from multiple cluster groups.
	 * We don't have enough credits to relink them all, and the
	 * cluster groups will be staying in cache for the duration of
	 * this operation.
	 */
	ac->ac_disable_chain_relink = 1;

	/* Claim the first region */
	status = ocfs2_block_group_claim_bits(osb, handle, ac, min_bits,
					      &bit_off, &num_bits);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}
	min_bits = num_bits;

	/* setup the group */
	bg_blkno = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_block_group_alloc_discontig(
				(unsigned long long)bg_blkno, alloc_rec);

	bg_bh = sb_getblk(osb->sb, bg_blkno);
	if (!bg_bh) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(alloc_inode), bg_bh);

	status = ocfs2_block_group_fill(handle, alloc_inode, bg_bh,
					bg_blkno, num_bits, alloc_rec, cl);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_block_group_grow_discontig(handle, alloc_inode,
						  bg_bh, ac, cl, min_bits);
	if (status)
		mlog_errno(status);

bail:
	if (status)
		ocfs2_bg_alloc_cleanup(handle, ac, alloc_inode, bg_bh);
	return status ? ERR_PTR(status) : bg_bh;
}