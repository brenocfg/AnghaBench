#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_path {TYPE_1__* p_node; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_next_free_rec; TYPE_2__* l_recs; } ;
struct ocfs2_extent_block {scalar_t__ h_blkno; scalar_t__ h_next_leaf_blk; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {scalar_t__ e_blkno; } ;
struct TYPE_3__ {struct buffer_head* bh; struct ocfs2_extent_list* el; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_unlink_path (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_cached_dealloc_ctxt*,struct ocfs2_path*,int) ; 
 struct buffer_head* path_leaf_bh (struct ocfs2_path*) ; 

__attribute__((used)) static void ocfs2_unlink_subtree(handle_t *handle,
				 struct ocfs2_extent_tree *et,
				 struct ocfs2_path *left_path,
				 struct ocfs2_path *right_path,
				 int subtree_index,
				 struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int i;
	struct buffer_head *root_bh = left_path->p_node[subtree_index].bh;
	struct ocfs2_extent_list *root_el = left_path->p_node[subtree_index].el;
	struct ocfs2_extent_block *eb;

	eb = (struct ocfs2_extent_block *)right_path->p_node[subtree_index + 1].bh->b_data;

	for(i = 1; i < le16_to_cpu(root_el->l_next_free_rec); i++)
		if (root_el->l_recs[i].e_blkno == eb->h_blkno)
			break;

	BUG_ON(i >= le16_to_cpu(root_el->l_next_free_rec));

	memset(&root_el->l_recs[i], 0, sizeof(struct ocfs2_extent_rec));
	le16_add_cpu(&root_el->l_next_free_rec, -1);

	eb = (struct ocfs2_extent_block *)path_leaf_bh(left_path)->b_data;
	eb->h_next_leaf_blk = 0;

	ocfs2_journal_dirty(handle, root_bh);
	ocfs2_journal_dirty(handle, path_leaf_bh(left_path));

	ocfs2_unlink_path(handle, et, dealloc, right_path,
			  subtree_index + 1);
}