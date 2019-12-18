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
struct ocfs2_path {int p_tree_depth; TYPE_1__* p_node; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct buffer_head* bh; struct ocfs2_extent_list* el; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_adjust_adjacent_records (struct ocfs2_extent_rec*,struct ocfs2_extent_rec*,struct ocfs2_extent_list*) ; 
 int /*<<< orphan*/  ocfs2_adjust_root_records (struct ocfs2_extent_list*,struct ocfs2_extent_list*,struct ocfs2_extent_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  trace_ocfs2_complete_edge_insert (int) ; 

__attribute__((used)) static void ocfs2_complete_edge_insert(handle_t *handle,
				       struct ocfs2_path *left_path,
				       struct ocfs2_path *right_path,
				       int subtree_index)
{
	int i, idx;
	struct ocfs2_extent_list *el, *left_el, *right_el;
	struct ocfs2_extent_rec *left_rec, *right_rec;
	struct buffer_head *root_bh = left_path->p_node[subtree_index].bh;

	/*
	 * Update the counts and position values within all the
	 * interior nodes to reflect the leaf rotation we just did.
	 *
	 * The root node is handled below the loop.
	 *
	 * We begin the loop with right_el and left_el pointing to the
	 * leaf lists and work our way up.
	 *
	 * NOTE: within this loop, left_el and right_el always refer
	 * to the *child* lists.
	 */
	left_el = path_leaf_el(left_path);
	right_el = path_leaf_el(right_path);
	for(i = left_path->p_tree_depth - 1; i > subtree_index; i--) {
		trace_ocfs2_complete_edge_insert(i);

		/*
		 * One nice property of knowing that all of these
		 * nodes are below the root is that we only deal with
		 * the leftmost right node record and the rightmost
		 * left node record.
		 */
		el = left_path->p_node[i].el;
		idx = le16_to_cpu(left_el->l_next_free_rec) - 1;
		left_rec = &el->l_recs[idx];

		el = right_path->p_node[i].el;
		right_rec = &el->l_recs[0];

		ocfs2_adjust_adjacent_records(left_rec, right_rec, right_el);

		ocfs2_journal_dirty(handle, left_path->p_node[i].bh);
		ocfs2_journal_dirty(handle, right_path->p_node[i].bh);

		/*
		 * Setup our list pointers now so that the current
		 * parents become children in the next iteration.
		 */
		left_el = left_path->p_node[i].el;
		right_el = right_path->p_node[i].el;
	}

	/*
	 * At the root node, adjust the two adjacent records which
	 * begin our path to the leaves.
	 */

	el = left_path->p_node[subtree_index].el;
	left_el = left_path->p_node[subtree_index + 1].el;
	right_el = right_path->p_node[subtree_index + 1].el;

	ocfs2_adjust_root_records(el, left_el, right_el,
				  left_path->p_node[subtree_index + 1].bh->b_blocknr);

	root_bh = left_path->p_node[subtree_index].bh;

	ocfs2_journal_dirty(handle, root_bh);
}