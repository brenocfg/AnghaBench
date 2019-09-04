#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct ocfs2_path {int /*<<< orphan*/  p_tree_depth; TYPE_2__* p_node; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int /*<<< orphan*/ * l_recs; } ;
struct TYPE_5__ {TYPE_1__* bh; } ;
struct TYPE_4__ {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_cp_path (struct ocfs2_path*,struct ocfs2_path*) ; 
 int ocfs2_extend_rotate_transaction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ocfs2_path*) ; 
 int ocfs2_find_cpos_for_right_leaf (struct super_block*,struct ocfs2_path*,scalar_t__*) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,scalar_t__) ; 
 int ocfs2_find_subtree_root (struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_is_empty_extent (int /*<<< orphan*/ *) ; 
 struct super_block* ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_mv_path (struct ocfs2_path*,struct ocfs2_path*) ; 
 struct ocfs2_path* ocfs2_new_path_from_path (struct ocfs2_path*) ; 
 int ocfs2_path_bh_journal_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int ocfs2_rotate_subtree_left (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_path*,int,struct ocfs2_cached_dealloc_ctxt*,int*) ; 
 TYPE_3__* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  trace_ocfs2_rotate_subtree (int,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ocfs2_rotate_tree_left(handle_t *handle,
				    struct ocfs2_extent_tree *et,
				    int orig_credits,
				    struct ocfs2_path *path,
				    struct ocfs2_cached_dealloc_ctxt *dealloc,
				    struct ocfs2_path **empty_extent_path)
{
	int ret, subtree_root, deleted;
	u32 right_cpos;
	struct ocfs2_path *left_path = NULL;
	struct ocfs2_path *right_path = NULL;
	struct super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);

	if (!ocfs2_is_empty_extent(&(path_leaf_el(path)->l_recs[0])))
		return 0;

	*empty_extent_path = NULL;

	ret = ocfs2_find_cpos_for_right_leaf(sb, path, &right_cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	left_path = ocfs2_new_path_from_path(path);
	if (!left_path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ocfs2_cp_path(left_path, path);

	right_path = ocfs2_new_path_from_path(path);
	if (!right_path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	while (right_cpos) {
		ret = ocfs2_find_path(et->et_ci, right_path, right_cpos);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		subtree_root = ocfs2_find_subtree_root(et, left_path,
						       right_path);

		trace_ocfs2_rotate_subtree(subtree_root,
		     (unsigned long long)
		     right_path->p_node[subtree_root].bh->b_blocknr,
		     right_path->p_tree_depth);

		ret = ocfs2_extend_rotate_transaction(handle, 0,
						      orig_credits, left_path);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		/*
		 * Caller might still want to make changes to the
		 * tree root, so re-add it to the journal here.
		 */
		ret = ocfs2_path_bh_journal_access(handle, et->et_ci,
						   left_path, 0);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_rotate_subtree_left(handle, et, left_path,
						right_path, subtree_root,
						dealloc, &deleted);
		if (ret == -EAGAIN) {
			/*
			 * The rotation has to temporarily stop due to
			 * the right subtree having an empty
			 * extent. Pass it back to the caller for a
			 * fixup.
			 */
			*empty_extent_path = right_path;
			right_path = NULL;
			goto out;
		}
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		/*
		 * The subtree rotate might have removed records on
		 * the rightmost edge. If so, then rotation is
		 * complete.
		 */
		if (deleted)
			break;

		ocfs2_mv_path(left_path, right_path);

		ret = ocfs2_find_cpos_for_right_leaf(sb, left_path,
						     &right_cpos);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

out:
	ocfs2_free_path(right_path);
	ocfs2_free_path(left_path);

	return ret;
}