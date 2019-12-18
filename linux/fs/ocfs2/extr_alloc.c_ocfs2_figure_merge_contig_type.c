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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct ocfs2_path {scalar_t__ p_tree_depth; } ;
struct ocfs2_merge_ctxt {int c_contig_type; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {scalar_t__ e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; int /*<<< orphan*/  l_count; } ;
struct ocfs2_extent_block {int /*<<< orphan*/  h_blkno; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  enum ocfs2_contig_type { ____Placeholder_ocfs2_contig_type } ocfs2_contig_type ;

/* Variables and functions */
 int CONTIG_LEFT ; 
 int CONTIG_LEFTRIGHT ; 
 int CONTIG_NONE ; 
 int CONTIG_RIGHT ; 
 int ENOMEM ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_error (struct super_block*,char*,unsigned long long,int,...) ; 
 int ocfs2_et_extent_contig (struct ocfs2_extent_tree*,struct ocfs2_extent_rec*,struct ocfs2_extent_rec*) ; 
 int ocfs2_find_cpos_for_left_leaf (struct super_block*,struct ocfs2_path*,scalar_t__*) ; 
 int ocfs2_find_cpos_for_right_leaf (struct super_block*,struct ocfs2_path*,scalar_t__*) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 scalar_t__ ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 struct super_block* ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_path (struct ocfs2_path*) ; 
 struct buffer_head* path_leaf_bh (struct ocfs2_path*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_figure_merge_contig_type(struct ocfs2_extent_tree *et,
			       struct ocfs2_path *path,
			       struct ocfs2_extent_list *el, int index,
			       struct ocfs2_extent_rec *split_rec,
			       struct ocfs2_merge_ctxt *ctxt)
{
	int status = 0;
	enum ocfs2_contig_type ret = CONTIG_NONE;
	u32 left_cpos, right_cpos;
	struct ocfs2_extent_rec *rec = NULL;
	struct ocfs2_extent_list *new_el;
	struct ocfs2_path *left_path = NULL, *right_path = NULL;
	struct buffer_head *bh;
	struct ocfs2_extent_block *eb;
	struct super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);

	if (index > 0) {
		rec = &el->l_recs[index - 1];
	} else if (path->p_tree_depth > 0) {
		status = ocfs2_find_cpos_for_left_leaf(sb, path, &left_cpos);
		if (status)
			goto exit;

		if (left_cpos != 0) {
			left_path = ocfs2_new_path_from_path(path);
			if (!left_path) {
				status = -ENOMEM;
				mlog_errno(status);
				goto exit;
			}

			status = ocfs2_find_path(et->et_ci, left_path,
						 left_cpos);
			if (status)
				goto free_left_path;

			new_el = path_leaf_el(left_path);

			if (le16_to_cpu(new_el->l_next_free_rec) !=
			    le16_to_cpu(new_el->l_count)) {
				bh = path_leaf_bh(left_path);
				eb = (struct ocfs2_extent_block *)bh->b_data;
				status = ocfs2_error(sb,
						"Extent block #%llu has an invalid l_next_free_rec of %d.  It should have matched the l_count of %d\n",
						(unsigned long long)le64_to_cpu(eb->h_blkno),
						le16_to_cpu(new_el->l_next_free_rec),
						le16_to_cpu(new_el->l_count));
				goto free_left_path;
			}
			rec = &new_el->l_recs[
				le16_to_cpu(new_el->l_next_free_rec) - 1];
		}
	}

	/*
	 * We're careful to check for an empty extent record here -
	 * the merge code will know what to do if it sees one.
	 */
	if (rec) {
		if (index == 1 && ocfs2_is_empty_extent(rec)) {
			if (split_rec->e_cpos == el->l_recs[index].e_cpos)
				ret = CONTIG_RIGHT;
		} else {
			ret = ocfs2_et_extent_contig(et, rec, split_rec);
		}
	}

	rec = NULL;
	if (index < (le16_to_cpu(el->l_next_free_rec) - 1))
		rec = &el->l_recs[index + 1];
	else if (le16_to_cpu(el->l_next_free_rec) == le16_to_cpu(el->l_count) &&
		 path->p_tree_depth > 0) {
		status = ocfs2_find_cpos_for_right_leaf(sb, path, &right_cpos);
		if (status)
			goto free_left_path;

		if (right_cpos == 0)
			goto free_left_path;

		right_path = ocfs2_new_path_from_path(path);
		if (!right_path) {
			status = -ENOMEM;
			mlog_errno(status);
			goto free_left_path;
		}

		status = ocfs2_find_path(et->et_ci, right_path, right_cpos);
		if (status)
			goto free_right_path;

		new_el = path_leaf_el(right_path);
		rec = &new_el->l_recs[0];
		if (ocfs2_is_empty_extent(rec)) {
			if (le16_to_cpu(new_el->l_next_free_rec) <= 1) {
				bh = path_leaf_bh(right_path);
				eb = (struct ocfs2_extent_block *)bh->b_data;
				status = ocfs2_error(sb,
						"Extent block #%llu has an invalid l_next_free_rec of %d\n",
						(unsigned long long)le64_to_cpu(eb->h_blkno),
						le16_to_cpu(new_el->l_next_free_rec));
				goto free_right_path;
			}
			rec = &new_el->l_recs[1];
		}
	}

	if (rec) {
		enum ocfs2_contig_type contig_type;

		contig_type = ocfs2_et_extent_contig(et, rec, split_rec);

		if (contig_type == CONTIG_LEFT && ret == CONTIG_RIGHT)
			ret = CONTIG_LEFTRIGHT;
		else if (ret == CONTIG_NONE)
			ret = contig_type;
	}

free_right_path:
	ocfs2_free_path(right_path);
free_left_path:
	ocfs2_free_path(left_path);
exit:
	if (status == 0)
		ctxt->c_contig_type = ret;

	return status;
}