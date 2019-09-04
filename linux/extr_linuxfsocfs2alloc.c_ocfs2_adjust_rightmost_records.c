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
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_int_clusters; int /*<<< orphan*/  e_leaf_clusters; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct ocfs2_extent_list* el; struct buffer_head* bh; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_adjust_rightmost_records(handle_t *handle,
					   struct ocfs2_extent_tree *et,
					   struct ocfs2_path *path,
					   struct ocfs2_extent_rec *insert_rec)
{
	int i, next_free;
	struct buffer_head *bh;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;

	/*
	 * Update everything except the leaf block.
	 */
	for (i = 0; i < path->p_tree_depth; i++) {
		bh = path->p_node[i].bh;
		el = path->p_node[i].el;

		next_free = le16_to_cpu(el->l_next_free_rec);
		if (next_free == 0) {
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu has a bad extent list\n",
				    (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci));
			return;
		}

		rec = &el->l_recs[next_free - 1];

		rec->e_int_clusters = insert_rec->e_cpos;
		le32_add_cpu(&rec->e_int_clusters,
			     le16_to_cpu(insert_rec->e_leaf_clusters));
		le32_add_cpu(&rec->e_int_clusters,
			     -le32_to_cpu(rec->e_cpos));

		ocfs2_journal_dirty(handle, bh);
	}
}