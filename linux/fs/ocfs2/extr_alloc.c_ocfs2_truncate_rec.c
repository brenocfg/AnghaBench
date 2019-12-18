#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct ocfs2_path {scalar_t__ p_tree_depth; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_blkno; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_extent_block {scalar_t__ h_next_leaf_blk; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;
struct TYPE_12__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_adjust_rightmost_records (TYPE_1__*,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_cleanup_merge (struct ocfs2_extent_list*,int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_complete_edge_insert (TYPE_1__*,struct ocfs2_path*,struct ocfs2_path*,int) ; 
 int ocfs2_extend_rotate_transaction (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_path*) ; 
 int ocfs2_find_cpos_for_left_leaf (struct super_block*,struct ocfs2_path*,scalar_t__*) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,scalar_t__) ; 
 int ocfs2_find_subtree_root (struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 scalar_t__ ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 int ocfs2_journal_access_path (int /*<<< orphan*/ ,TYPE_1__*,struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (TYPE_1__*,TYPE_2__*) ; 
 struct super_block* ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_path (struct ocfs2_path*) ; 
 scalar_t__ ocfs2_rec_clusters (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int ocfs2_rotate_tree_left (TYPE_1__*,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_cached_dealloc_ctxt*) ; 
 TYPE_2__* path_leaf_bh (struct ocfs2_path*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_truncate_rec(handle_t *handle,
			      struct ocfs2_extent_tree *et,
			      struct ocfs2_path *path, int index,
			      struct ocfs2_cached_dealloc_ctxt *dealloc,
			      u32 cpos, u32 len)
{
	int ret;
	u32 left_cpos, rec_range, trunc_range;
	int is_rightmost_tree_rec = 0;
	struct super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	struct ocfs2_path *left_path = NULL;
	struct ocfs2_extent_list *el = path_leaf_el(path);
	struct ocfs2_extent_rec *rec;
	struct ocfs2_extent_block *eb;

	if (ocfs2_is_empty_extent(&el->l_recs[0]) && index > 0) {
		/* extend credit for ocfs2_remove_rightmost_path */
		ret = ocfs2_extend_rotate_transaction(handle, 0,
				handle->h_buffer_credits,
				path);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		index--;
	}

	if (index == (le16_to_cpu(el->l_next_free_rec) - 1) &&
	    path->p_tree_depth) {
		/*
		 * Check whether this is the rightmost tree record. If
		 * we remove all of this record or part of its right
		 * edge then an update of the record lengths above it
		 * will be required.
		 */
		eb = (struct ocfs2_extent_block *)path_leaf_bh(path)->b_data;
		if (eb->h_next_leaf_blk == 0)
			is_rightmost_tree_rec = 1;
	}

	rec = &el->l_recs[index];
	if (index == 0 && path->p_tree_depth &&
	    le32_to_cpu(rec->e_cpos) == cpos) {
		/*
		 * Changing the leftmost offset (via partial or whole
		 * record truncate) of an interior (or rightmost) path
		 * means we have to update the subtree that is formed
		 * by this leaf and the one to it's left.
		 *
		 * There are two cases we can skip:
		 *   1) Path is the leftmost one in our btree.
		 *   2) The leaf is rightmost and will be empty after
		 *      we remove the extent record - the rotate code
		 *      knows how to update the newly formed edge.
		 */

		ret = ocfs2_find_cpos_for_left_leaf(sb, path, &left_cpos);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		if (left_cpos && le16_to_cpu(el->l_next_free_rec) > 1) {
			left_path = ocfs2_new_path_from_path(path);
			if (!left_path) {
				ret = -ENOMEM;
				mlog_errno(ret);
				goto out;
			}

			ret = ocfs2_find_path(et->et_ci, left_path,
					      left_cpos);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		}
	}

	ret = ocfs2_extend_rotate_transaction(handle, 0,
					      handle->h_buffer_credits,
					      path);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_path(et->et_ci, handle, path);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_path(et->et_ci, handle, left_path);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	rec_range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);
	trunc_range = cpos + len;

	if (le32_to_cpu(rec->e_cpos) == cpos && rec_range == trunc_range) {
		int next_free;

		memset(rec, 0, sizeof(*rec));
		ocfs2_cleanup_merge(el, index);

		next_free = le16_to_cpu(el->l_next_free_rec);
		if (is_rightmost_tree_rec && next_free > 1) {
			/*
			 * We skip the edge update if this path will
			 * be deleted by the rotate code.
			 */
			rec = &el->l_recs[next_free - 1];
			ocfs2_adjust_rightmost_records(handle, et, path,
						       rec);
		}
	} else if (le32_to_cpu(rec->e_cpos) == cpos) {
		/* Remove leftmost portion of the record. */
		le32_add_cpu(&rec->e_cpos, len);
		le64_add_cpu(&rec->e_blkno, ocfs2_clusters_to_blocks(sb, len));
		le16_add_cpu(&rec->e_leaf_clusters, -len);
	} else if (rec_range == trunc_range) {
		/* Remove rightmost portion of the record */
		le16_add_cpu(&rec->e_leaf_clusters, -len);
		if (is_rightmost_tree_rec)
			ocfs2_adjust_rightmost_records(handle, et, path, rec);
	} else {
		/* Caller should have trapped this. */
		mlog(ML_ERROR, "Owner %llu: Invalid record truncate: (%u, %u) "
		     "(%u, %u)\n",
		     (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
		     le32_to_cpu(rec->e_cpos),
		     le16_to_cpu(rec->e_leaf_clusters), cpos, len);
		BUG();
	}

	if (left_path) {
		int subtree_index;

		subtree_index = ocfs2_find_subtree_root(et, left_path, path);
		ocfs2_complete_edge_insert(handle, left_path, path,
					   subtree_index);
	}

	ocfs2_journal_dirty(handle, path_leaf_bh(path));

	ret = ocfs2_rotate_tree_left(handle, et, path, dealloc);
	if (ret)
		mlog_errno(ret);

out:
	ocfs2_free_path(left_path);
	return ret;
}