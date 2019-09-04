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
struct ocfs2_xattr_header {int dummy; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  l_next_free_rec; int /*<<< orphan*/  l_tree_depth; } ;
struct ocfs2_refcount_block {TYPE_1__ rf_list; int /*<<< orphan*/  rf_flags; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int OCFS2_EXPAND_REFCOUNT_TREE_CREDITS ; 
 int OCFS2_REFCOUNT_TREE_FL ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_get_xattr_value_root ; 
 int ocfs2_refcount_recs_per_rb (int /*<<< orphan*/ ) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_value_metas_in_xattr_header (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_xattr_header*,int*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_reflink_lock_xattr_allocators(struct ocfs2_super *osb,
					struct ocfs2_xattr_header *xh,
					struct buffer_head *ref_root_bh,
					int *credits,
					struct ocfs2_alloc_context **meta_ac)
{
	int ret, meta_add = 0, num_recs = 0;
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_root_bh->b_data;

	*credits = 0;

	ret = ocfs2_value_metas_in_xattr_header(osb->sb, NULL, xh,
						&meta_add, credits, &num_recs,
						ocfs2_get_xattr_value_root,
						NULL);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * We need to add/modify num_recs in refcount tree, so just calculate
	 * an approximate number we need for refcount tree change.
	 * Sometimes we need to split the tree, and after split,  half recs
	 * will be moved to the new block, and a new block can only provide
	 * half number of recs. So we multiple new blocks by 2.
	 */
	num_recs = num_recs / ocfs2_refcount_recs_per_rb(osb->sb) * 2;
	meta_add += num_recs;
	*credits += num_recs + num_recs * OCFS2_EXPAND_REFCOUNT_TREE_CREDITS;
	if (le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)
		*credits += le16_to_cpu(rb->rf_list.l_tree_depth) *
			    le16_to_cpu(rb->rf_list.l_next_free_rec) + 1;
	else
		*credits += 1;

	ret = ocfs2_reserve_new_metadata_blocks(osb, meta_add, meta_ac);
	if (ret)
		mlog_errno(ret);

out:
	return ret;
}