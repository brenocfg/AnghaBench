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
struct ocfs2_extent_tree_operations {int /*<<< orphan*/  (* eo_fill_max_leaf_clusters ) (struct ocfs2_extent_tree*) ;int /*<<< orphan*/  (* eo_fill_root_el ) (struct ocfs2_extent_tree*) ;} ;
struct ocfs2_extent_tree {struct ocfs2_extent_tree_operations const* et_ops; scalar_t__ et_max_leaf_clusters; int /*<<< orphan*/ * et_dealloc; void* et_object; int /*<<< orphan*/  et_root_journal_access; struct ocfs2_caching_info* et_ci; struct buffer_head* et_root_bh; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  ocfs2_journal_access_func ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ocfs2_extent_tree*) ; 
 int /*<<< orphan*/  stub2 (struct ocfs2_extent_tree*) ; 

__attribute__((used)) static void __ocfs2_init_extent_tree(struct ocfs2_extent_tree *et,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *bh,
				     ocfs2_journal_access_func access,
				     void *obj,
				     const struct ocfs2_extent_tree_operations *ops)
{
	et->et_ops = ops;
	et->et_root_bh = bh;
	et->et_ci = ci;
	et->et_root_journal_access = access;
	if (!obj)
		obj = (void *)bh->b_data;
	et->et_object = obj;
	et->et_dealloc = NULL;

	et->et_ops->eo_fill_root_el(et);
	if (!et->et_ops->eo_fill_max_leaf_clusters)
		et->et_max_leaf_clusters = 0;
	else
		et->et_ops->eo_fill_max_leaf_clusters(et);
}