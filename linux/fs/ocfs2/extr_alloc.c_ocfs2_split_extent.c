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
struct ocfs2_path {scalar_t__ p_tree_depth; } ;
struct ocfs2_merge_ctxt {int c_split_covers_rec; scalar_t__ c_contig_type; int /*<<< orphan*/  c_has_empty_extent; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {scalar_t__ e_cpos; scalar_t__ e_leaf_clusters; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ CONTIG_NONE ; 
 int EIO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_et_get_last_eb_blk (struct ocfs2_extent_tree*) ; 
 int ocfs2_figure_merge_contig_type (struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_extent_list*,int,struct ocfs2_extent_rec*,struct ocfs2_merge_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 int ocfs2_read_extent_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int ocfs2_replace_extent_rec (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_extent_list*,int,struct ocfs2_extent_rec*) ; 
 int ocfs2_split_and_insert (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,struct buffer_head**,int,struct ocfs2_extent_rec*,struct ocfs2_alloc_context*) ; 
 int ocfs2_try_to_merge_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,int,struct ocfs2_extent_rec*,struct ocfs2_cached_dealloc_ctxt*,struct ocfs2_merge_ctxt*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  trace_ocfs2_split_extent (int,scalar_t__,int /*<<< orphan*/ ,int) ; 

int ocfs2_split_extent(handle_t *handle,
		       struct ocfs2_extent_tree *et,
		       struct ocfs2_path *path,
		       int split_index,
		       struct ocfs2_extent_rec *split_rec,
		       struct ocfs2_alloc_context *meta_ac,
		       struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret = 0;
	struct ocfs2_extent_list *el = path_leaf_el(path);
	struct buffer_head *last_eb_bh = NULL;
	struct ocfs2_extent_rec *rec = &el->l_recs[split_index];
	struct ocfs2_merge_ctxt ctxt;

	if (le32_to_cpu(rec->e_cpos) > le32_to_cpu(split_rec->e_cpos) ||
	    ((le32_to_cpu(rec->e_cpos) + le16_to_cpu(rec->e_leaf_clusters)) <
	     (le32_to_cpu(split_rec->e_cpos) + le16_to_cpu(split_rec->e_leaf_clusters)))) {
		ret = -EIO;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_figure_merge_contig_type(et, path, el,
					     split_index,
					     split_rec,
					     &ctxt);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * The core merge / split code wants to know how much room is
	 * left in this allocation tree, so we pass the
	 * rightmost extent list.
	 */
	if (path->p_tree_depth) {
		ret = ocfs2_read_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &last_eb_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	if (rec->e_cpos == split_rec->e_cpos &&
	    rec->e_leaf_clusters == split_rec->e_leaf_clusters)
		ctxt.c_split_covers_rec = 1;
	else
		ctxt.c_split_covers_rec = 0;

	ctxt.c_has_empty_extent = ocfs2_is_empty_extent(&el->l_recs[0]);

	trace_ocfs2_split_extent(split_index, ctxt.c_contig_type,
				 ctxt.c_has_empty_extent,
				 ctxt.c_split_covers_rec);

	if (ctxt.c_contig_type == CONTIG_NONE) {
		if (ctxt.c_split_covers_rec)
			ret = ocfs2_replace_extent_rec(handle, et, path, el,
						       split_index, split_rec);
		else
			ret = ocfs2_split_and_insert(handle, et, path,
						     &last_eb_bh, split_index,
						     split_rec, meta_ac);
		if (ret)
			mlog_errno(ret);
	} else {
		ret = ocfs2_try_to_merge_extent(handle, et, path,
						split_index, split_rec,
						dealloc, &ctxt);
		if (ret)
			mlog_errno(ret);
	}

out:
	brelse(last_eb_bh);
	return ret;
}