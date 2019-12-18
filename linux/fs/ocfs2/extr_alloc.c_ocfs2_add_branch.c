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
typedef  scalar_t__ u32 ;
struct ocfs2_extent_tree {struct buffer_head* et_root_bh; int /*<<< orphan*/  et_ci; struct ocfs2_extent_list* et_root_el; } ;
struct ocfs2_extent_list {void* l_next_free_rec; TYPE_1__* l_recs; void* l_tree_depth; } ;
struct ocfs2_extent_block {void* h_next_leaf_blk; int /*<<< orphan*/  h_blkno; struct ocfs2_extent_list h_list; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {void* e_int_clusters; void* e_cpos; void* e_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_EXTENT_BLOCK (struct ocfs2_extent_block*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct buffer_head** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 int /*<<< orphan*/  le16_add_cpu (void**,int) ; 
 int le16_to_cpu (void*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_adjust_rightmost_branch (int /*<<< orphan*/ *,struct ocfs2_extent_tree*) ; 
 int ocfs2_create_new_meta_bhs (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int,struct ocfs2_alloc_context*,struct buffer_head**) ; 
 int ocfs2_et_root_journal_access (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_et_set_last_eb_blk (struct ocfs2_extent_tree*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_is_dealloc_empty (struct ocfs2_extent_tree*) ; 
 int ocfs2_journal_access_eb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 int ocfs2_reuse_blk_from_dealloc (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct buffer_head**,int,int*) ; 
 scalar_t__ ocfs2_sum_rightmost_rec (struct ocfs2_extent_list*) ; 
 int /*<<< orphan*/  trace_ocfs2_adjust_rightmost_branch (unsigned long long,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ocfs2_add_branch(handle_t *handle,
			    struct ocfs2_extent_tree *et,
			    struct buffer_head *eb_bh,
			    struct buffer_head **last_eb_bh,
			    struct ocfs2_alloc_context *meta_ac)
{
	int status, new_blocks, i, block_given = 0;
	u64 next_blkno, new_last_eb_blk;
	struct buffer_head *bh;
	struct buffer_head **new_eb_bhs = NULL;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list  *eb_el;
	struct ocfs2_extent_list  *el;
	u32 new_cpos, root_end;

	BUG_ON(!last_eb_bh || !*last_eb_bh);

	if (eb_bh) {
		eb = (struct ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;
	} else
		el = et->et_root_el;

	/* we never add a branch to a leaf. */
	BUG_ON(!el->l_tree_depth);

	new_blocks = le16_to_cpu(el->l_tree_depth);

	eb = (struct ocfs2_extent_block *)(*last_eb_bh)->b_data;
	new_cpos = ocfs2_sum_rightmost_rec(&eb->h_list);
	root_end = ocfs2_sum_rightmost_rec(et->et_root_el);

	/*
	 * If there is a gap before the root end and the real end
	 * of the righmost leaf block, we need to remove the gap
	 * between new_cpos and root_end first so that the tree
	 * is consistent after we add a new branch(it will start
	 * from new_cpos).
	 */
	if (root_end > new_cpos) {
		trace_ocfs2_adjust_rightmost_branch(
			(unsigned long long)
			ocfs2_metadata_cache_owner(et->et_ci),
			root_end, new_cpos);

		status = ocfs2_adjust_rightmost_branch(handle, et);
		if (status) {
			mlog_errno(status);
			goto bail;
		}
	}

	/* allocate the number of new eb blocks we need */
	new_eb_bhs = kcalloc(new_blocks, sizeof(struct buffer_head *),
			     GFP_KERNEL);
	if (!new_eb_bhs) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	/* Firstyly, try to reuse dealloc since we have already estimated how
	 * many extent blocks we may use.
	 */
	if (!ocfs2_is_dealloc_empty(et)) {
		status = ocfs2_reuse_blk_from_dealloc(handle, et,
						      new_eb_bhs, new_blocks,
						      &block_given);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	BUG_ON(block_given > new_blocks);

	if (block_given < new_blocks) {
		BUG_ON(!meta_ac);
		status = ocfs2_create_new_meta_bhs(handle, et,
						   new_blocks - block_given,
						   meta_ac,
						   &new_eb_bhs[block_given]);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	/* Note: new_eb_bhs[new_blocks - 1] is the guy which will be
	 * linked with the rest of the tree.
	 * conversly, new_eb_bhs[0] is the new bottommost leaf.
	 *
	 * when we leave the loop, new_last_eb_blk will point to the
	 * newest leaf, and next_blkno will point to the topmost extent
	 * block. */
	next_blkno = new_last_eb_blk = 0;
	for(i = 0; i < new_blocks; i++) {
		bh = new_eb_bhs[i];
		eb = (struct ocfs2_extent_block *) bh->b_data;
		/* ocfs2_create_new_meta_bhs() should create it right! */
		BUG_ON(!OCFS2_IS_VALID_EXTENT_BLOCK(eb));
		eb_el = &eb->h_list;

		status = ocfs2_journal_access_eb(handle, et->et_ci, bh,
						 OCFS2_JOURNAL_ACCESS_CREATE);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		eb->h_next_leaf_blk = 0;
		eb_el->l_tree_depth = cpu_to_le16(i);
		eb_el->l_next_free_rec = cpu_to_le16(1);
		/*
		 * This actually counts as an empty extent as
		 * c_clusters == 0
		 */
		eb_el->l_recs[0].e_cpos = cpu_to_le32(new_cpos);
		eb_el->l_recs[0].e_blkno = cpu_to_le64(next_blkno);
		/*
		 * eb_el isn't always an interior node, but even leaf
		 * nodes want a zero'd flags and reserved field so
		 * this gets the whole 32 bits regardless of use.
		 */
		eb_el->l_recs[0].e_int_clusters = cpu_to_le32(0);
		if (!eb_el->l_tree_depth)
			new_last_eb_blk = le64_to_cpu(eb->h_blkno);

		ocfs2_journal_dirty(handle, bh);
		next_blkno = le64_to_cpu(eb->h_blkno);
	}

	/* This is a bit hairy. We want to update up to three blocks
	 * here without leaving any of them in an inconsistent state
	 * in case of error. We don't have to worry about
	 * journal_dirty erroring as it won't unless we've aborted the
	 * handle (in which case we would never be here) so reserving
	 * the write with journal_access is all we need to do. */
	status = ocfs2_journal_access_eb(handle, et->et_ci, *last_eb_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	status = ocfs2_et_root_journal_access(handle, et,
					      OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	if (eb_bh) {
		status = ocfs2_journal_access_eb(handle, et->et_ci, eb_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	/* Link the new branch into the rest of the tree (el will
	 * either be on the root_bh, or the extent block passed in. */
	i = le16_to_cpu(el->l_next_free_rec);
	el->l_recs[i].e_blkno = cpu_to_le64(next_blkno);
	el->l_recs[i].e_cpos = cpu_to_le32(new_cpos);
	el->l_recs[i].e_int_clusters = 0;
	le16_add_cpu(&el->l_next_free_rec, 1);

	/* fe needs a new last extent block pointer, as does the
	 * next_leaf on the previously last-extent-block. */
	ocfs2_et_set_last_eb_blk(et, new_last_eb_blk);

	eb = (struct ocfs2_extent_block *) (*last_eb_bh)->b_data;
	eb->h_next_leaf_blk = cpu_to_le64(new_last_eb_blk);

	ocfs2_journal_dirty(handle, *last_eb_bh);
	ocfs2_journal_dirty(handle, et->et_root_bh);
	if (eb_bh)
		ocfs2_journal_dirty(handle, eb_bh);

	/*
	 * Some callers want to track the rightmost leaf so pass it
	 * back here.
	 */
	brelse(*last_eb_bh);
	get_bh(new_eb_bhs[0]);
	*last_eb_bh = new_eb_bhs[0];

	status = 0;
bail:
	if (new_eb_bhs) {
		for (i = 0; i < new_blocks; i++)
			brelse(new_eb_bhs[i]);
		kfree(new_eb_bhs);
	}

	return status;
}