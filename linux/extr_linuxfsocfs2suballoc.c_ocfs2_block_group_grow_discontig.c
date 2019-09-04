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
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_count; int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_bits; struct ocfs2_extent_list bg_list; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_bpc; int /*<<< orphan*/  cl_cpg; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_bg_discontig_add_extent (struct ocfs2_super*,struct ocfs2_group_desc*,struct ocfs2_chain_list*,int /*<<< orphan*/ ,unsigned int) ; 
 int ocfs2_block_group_claim_bits (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,unsigned int) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_block_group_grow_discontig(handle_t *handle,
					    struct inode *alloc_inode,
					    struct buffer_head *bg_bh,
					    struct ocfs2_alloc_context *ac,
					    struct ocfs2_chain_list *cl,
					    unsigned int min_bits)
{
	int status;
	struct ocfs2_super *osb = OCFS2_SB(alloc_inode->i_sb);
	struct ocfs2_group_desc *bg =
		(struct ocfs2_group_desc *)bg_bh->b_data;
	unsigned int needed = le16_to_cpu(cl->cl_cpg) -
			 le16_to_cpu(bg->bg_bits) / le16_to_cpu(cl->cl_bpc);
	u32 p_cpos, clusters;
	u64 p_blkno;
	struct ocfs2_extent_list *el = &bg->bg_list;

	status = ocfs2_journal_access_gd(handle,
					 INODE_CACHE(alloc_inode),
					 bg_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	while ((needed > 0) && (le16_to_cpu(el->l_next_free_rec) <
				le16_to_cpu(el->l_count))) {
		if (min_bits > needed)
			min_bits = needed;
		status = ocfs2_block_group_claim_bits(osb, handle, ac,
						      min_bits, &p_cpos,
						      &clusters);
		if (status < 0) {
			if (status != -ENOSPC)
				mlog_errno(status);
			goto bail;
		}
		p_blkno = ocfs2_clusters_to_blocks(osb->sb, p_cpos);
		ocfs2_bg_discontig_add_extent(osb, bg, cl, p_blkno,
					      clusters);

		min_bits = clusters;
		needed = le16_to_cpu(cl->cl_cpg) -
			 le16_to_cpu(bg->bg_bits) / le16_to_cpu(cl->cl_bpc);
	}

	if (needed > 0) {
		/*
		 * We have used up all the extent rec but can't fill up
		 * the cpg. So bail out.
		 */
		status = -ENOSPC;
		goto bail;
	}

	ocfs2_journal_dirty(handle, bg_bh);

bail:
	return status;
}