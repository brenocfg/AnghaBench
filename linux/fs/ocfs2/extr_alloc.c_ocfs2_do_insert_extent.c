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
struct ocfs2_path {int dummy; } ;
struct ocfs2_insert_type {scalar_t__ ins_appending; scalar_t__ ins_contig; scalar_t__ ins_split; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_bh; int /*<<< orphan*/  et_ci; struct ocfs2_extent_list* et_root_el; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_tree_depth; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ APPEND_NONE ; 
 scalar_t__ APPEND_TAIL ; 
 scalar_t__ CONTIG_LEFT ; 
 scalar_t__ CONTIG_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 scalar_t__ SPLIT_NONE ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_append_rec_to_path (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_extent_rec*,struct ocfs2_path*,struct ocfs2_path**) ; 
 int ocfs2_et_root_journal_access (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_et_update_clusters (struct ocfs2_extent_tree*,scalar_t__) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_insert_at_leaf (struct ocfs2_extent_tree*,struct ocfs2_extent_rec*,struct ocfs2_extent_list*,struct ocfs2_insert_type*) ; 
 int ocfs2_insert_path (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_path*,struct ocfs2_extent_rec*,struct ocfs2_insert_type*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 int ocfs2_rotate_tree_right (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,scalar_t__,int /*<<< orphan*/ ,struct ocfs2_path*,struct ocfs2_path**) ; 

__attribute__((used)) static int ocfs2_do_insert_extent(handle_t *handle,
				  struct ocfs2_extent_tree *et,
				  struct ocfs2_extent_rec *insert_rec,
				  struct ocfs2_insert_type *type)
{
	int ret, rotate = 0;
	u32 cpos;
	struct ocfs2_path *right_path = NULL;
	struct ocfs2_path *left_path = NULL;
	struct ocfs2_extent_list *el;

	el = et->et_root_el;

	ret = ocfs2_et_root_journal_access(handle, et,
					   OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (le16_to_cpu(el->l_tree_depth) == 0) {
		ocfs2_insert_at_leaf(et, insert_rec, el, type);
		goto out_update_clusters;
	}

	right_path = ocfs2_new_path_from_et(et);
	if (!right_path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Determine the path to start with. Rotations need the
	 * rightmost path, everything else can go directly to the
	 * target leaf.
	 */
	cpos = le32_to_cpu(insert_rec->e_cpos);
	if (type->ins_appending == APPEND_NONE &&
	    type->ins_contig == CONTIG_NONE) {
		rotate = 1;
		cpos = UINT_MAX;
	}

	ret = ocfs2_find_path(et->et_ci, right_path, cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Rotations and appends need special treatment - they modify
	 * parts of the tree's above them.
	 *
	 * Both might pass back a path immediate to the left of the
	 * one being inserted to. This will be cause
	 * ocfs2_insert_path() to modify the rightmost records of
	 * left_path to account for an edge insert.
	 *
	 * XXX: When modifying this code, keep in mind that an insert
	 * can wind up skipping both of these two special cases...
	 */
	if (rotate) {
		ret = ocfs2_rotate_tree_right(handle, et, type->ins_split,
					      le32_to_cpu(insert_rec->e_cpos),
					      right_path, &left_path);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		/*
		 * ocfs2_rotate_tree_right() might have extended the
		 * transaction without re-journaling our tree root.
		 */
		ret = ocfs2_et_root_journal_access(handle, et,
						   OCFS2_JOURNAL_ACCESS_WRITE);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	} else if (type->ins_appending == APPEND_TAIL
		   && type->ins_contig != CONTIG_LEFT) {
		ret = ocfs2_append_rec_to_path(handle, et, insert_rec,
					       right_path, &left_path);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	ret = ocfs2_insert_path(handle, et, left_path, right_path,
				insert_rec, type);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

out_update_clusters:
	if (type->ins_split == SPLIT_NONE)
		ocfs2_et_update_clusters(et,
					 le16_to_cpu(insert_rec->e_leaf_clusters));

	ocfs2_journal_dirty(handle, et->et_root_bh);

out:
	ocfs2_free_path(left_path);
	ocfs2_free_path(right_path);

	return ret;
}