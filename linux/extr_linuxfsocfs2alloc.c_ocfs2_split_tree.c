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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_path {int p_tree_depth; } ;
struct ocfs2_insert_type {int ins_tree_depth; int /*<<< orphan*/  ins_split; int /*<<< orphan*/  ins_contig; int /*<<< orphan*/  ins_appending; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_el; int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_count; int /*<<< orphan*/  l_next_free_rec; struct ocfs2_extent_rec* l_recs; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_NONE ; 
 int /*<<< orphan*/  CONTIG_NONE ; 
 int /*<<< orphan*/  SPLIT_RIGHT ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_insert_type*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_do_insert_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_extent_rec*,struct ocfs2_insert_type*) ; 
 int /*<<< orphan*/  ocfs2_et_get_last_eb_blk (struct ocfs2_extent_tree*) ; 
 int ocfs2_extend_meta_needed (int /*<<< orphan*/ ) ; 
 int ocfs2_extend_trans (int /*<<< orphan*/ *,int) ; 
 int ocfs2_grow_tree (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int*,struct buffer_head**,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_make_right_split_rec (int /*<<< orphan*/ ,struct ocfs2_extent_rec*,int /*<<< orphan*/ ,struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 int ocfs2_read_extent_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_split_tree(handle_t *handle, struct ocfs2_extent_tree *et,
			    struct ocfs2_path *path,
			    int index, u32 new_range,
			    struct ocfs2_alloc_context *meta_ac)
{
	int ret, depth, credits;
	struct buffer_head *last_eb_bh = NULL;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list *rightmost_el, *el;
	struct ocfs2_extent_rec split_rec;
	struct ocfs2_extent_rec *rec;
	struct ocfs2_insert_type insert;

	/*
	 * Setup the record to split before we grow the tree.
	 */
	el = path_leaf_el(path);
	rec = &el->l_recs[index];
	ocfs2_make_right_split_rec(ocfs2_metadata_cache_get_super(et->et_ci),
				   &split_rec, new_range, rec);

	depth = path->p_tree_depth;
	if (depth > 0) {
		ret = ocfs2_read_extent_block(et->et_ci,
					      ocfs2_et_get_last_eb_blk(et),
					      &last_eb_bh);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		eb = (struct ocfs2_extent_block *) last_eb_bh->b_data;
		rightmost_el = &eb->h_list;
	} else
		rightmost_el = path_leaf_el(path);

	credits = path->p_tree_depth +
		  ocfs2_extend_meta_needed(et->et_root_el);
	ret = ocfs2_extend_trans(handle, credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (le16_to_cpu(rightmost_el->l_next_free_rec) ==
	    le16_to_cpu(rightmost_el->l_count)) {
		ret = ocfs2_grow_tree(handle, et, &depth, &last_eb_bh,
				      meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	memset(&insert, 0, sizeof(struct ocfs2_insert_type));
	insert.ins_appending = APPEND_NONE;
	insert.ins_contig = CONTIG_NONE;
	insert.ins_split = SPLIT_RIGHT;
	insert.ins_tree_depth = depth;

	ret = ocfs2_do_insert_extent(handle, et, &split_rec, &insert);
	if (ret)
		mlog_errno(ret);

out:
	brelse(last_eb_bh);
	return ret;
}