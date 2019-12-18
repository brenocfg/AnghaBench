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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_extent_tree {struct buffer_head* et_root_bh; int /*<<< orphan*/  et_ci; struct ocfs2_extent_list* et_root_el; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {scalar_t__ l_tree_depth; scalar_t__ l_next_free_rec; TYPE_1__* l_recs; } ;
struct ocfs2_extent_block {int /*<<< orphan*/  h_blkno; struct ocfs2_extent_list h_list; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  e_int_clusters; int /*<<< orphan*/  e_blkno; scalar_t__ e_cpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_EXTENT_BLOCK (struct ocfs2_extent_block*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_create_new_meta_bhs (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int,struct ocfs2_alloc_context*,struct buffer_head**) ; 
 int ocfs2_et_root_journal_access (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_et_set_last_eb_blk (struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_is_dealloc_empty (struct ocfs2_extent_tree*) ; 
 int ocfs2_journal_access_eb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_reuse_blk_from_dealloc (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct buffer_head**,int,int*) ; 
 int /*<<< orphan*/  ocfs2_sum_rightmost_rec (struct ocfs2_extent_list*) ; 

__attribute__((used)) static int ocfs2_shift_tree_depth(handle_t *handle,
				  struct ocfs2_extent_tree *et,
				  struct ocfs2_alloc_context *meta_ac,
				  struct buffer_head **ret_new_eb_bh)
{
	int status, i, block_given = 0;
	u32 new_clusters;
	struct buffer_head *new_eb_bh = NULL;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list  *root_el;
	struct ocfs2_extent_list  *eb_el;

	if (!ocfs2_is_dealloc_empty(et)) {
		status = ocfs2_reuse_blk_from_dealloc(handle, et,
						      &new_eb_bh, 1,
						      &block_given);
	} else if (meta_ac) {
		status = ocfs2_create_new_meta_bhs(handle, et, 1, meta_ac,
						   &new_eb_bh);

	} else {
		BUG();
	}

	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	eb = (struct ocfs2_extent_block *) new_eb_bh->b_data;
	/* ocfs2_create_new_meta_bhs() should create it right! */
	BUG_ON(!OCFS2_IS_VALID_EXTENT_BLOCK(eb));

	eb_el = &eb->h_list;
	root_el = et->et_root_el;

	status = ocfs2_journal_access_eb(handle, et->et_ci, new_eb_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	/* copy the root extent list data into the new extent block */
	eb_el->l_tree_depth = root_el->l_tree_depth;
	eb_el->l_next_free_rec = root_el->l_next_free_rec;
	for (i = 0; i < le16_to_cpu(root_el->l_next_free_rec); i++)
		eb_el->l_recs[i] = root_el->l_recs[i];

	ocfs2_journal_dirty(handle, new_eb_bh);

	status = ocfs2_et_root_journal_access(handle, et,
					      OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	new_clusters = ocfs2_sum_rightmost_rec(eb_el);

	/* update root_bh now */
	le16_add_cpu(&root_el->l_tree_depth, 1);
	root_el->l_recs[0].e_cpos = 0;
	root_el->l_recs[0].e_blkno = eb->h_blkno;
	root_el->l_recs[0].e_int_clusters = cpu_to_le32(new_clusters);
	for (i = 1; i < le16_to_cpu(root_el->l_next_free_rec); i++)
		memset(&root_el->l_recs[i], 0, sizeof(struct ocfs2_extent_rec));
	root_el->l_next_free_rec = cpu_to_le16(1);

	/* If this is our 1st tree depth shift, then last_eb_blk
	 * becomes the allocated extent block */
	if (root_el->l_tree_depth == cpu_to_le16(1))
		ocfs2_et_set_last_eb_blk(et, le64_to_cpu(eb->h_blkno));

	ocfs2_journal_dirty(handle, et->et_root_bh);

	*ret_new_eb_bh = new_eb_bh;
	new_eb_bh = NULL;
	status = 0;
bail:
	brelse(new_eb_bh);

	return status;
}