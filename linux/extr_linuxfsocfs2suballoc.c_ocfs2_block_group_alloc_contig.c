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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_cpg; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct buffer_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_block_group_fill (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,scalar_t__,int /*<<< orphan*/ ,unsigned int,struct ocfs2_chain_list*) ; 
 int ocfs2_claim_clusters (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ocfs2_find_smallest_chain (struct ocfs2_chain_list*) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_ocfs2_block_group_alloc_contig (unsigned long long,unsigned int) ; 

__attribute__((used)) static struct buffer_head *
ocfs2_block_group_alloc_contig(struct ocfs2_super *osb, handle_t *handle,
			       struct inode *alloc_inode,
			       struct ocfs2_alloc_context *ac,
			       struct ocfs2_chain_list *cl)
{
	int status;
	u32 bit_off, num_bits;
	u64 bg_blkno;
	struct buffer_head *bg_bh;
	unsigned int alloc_rec = ocfs2_find_smallest_chain(cl);

	status = ocfs2_claim_clusters(handle, ac,
				      le16_to_cpu(cl->cl_cpg), &bit_off,
				      &num_bits);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	/* setup the group */
	bg_blkno = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_block_group_alloc_contig(
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
		brelse(bg_bh);
		mlog_errno(status);
	}

bail:
	return status ? ERR_PTR(status) : bg_bh;
}