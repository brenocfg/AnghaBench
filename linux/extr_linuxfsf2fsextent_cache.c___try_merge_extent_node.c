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
struct f2fs_sb_info {int /*<<< orphan*/  extent_lock; int /*<<< orphan*/  extent_list; } ;
struct extent_tree {struct extent_node* cached_en; } ;
struct extent_info {scalar_t__ len; int /*<<< orphan*/  blk; int /*<<< orphan*/  fofs; } ;
struct extent_node {int /*<<< orphan*/  list; struct extent_info ei; } ;

/* Variables and functions */
 scalar_t__ __is_back_mergeable (struct extent_info*,struct extent_info*) ; 
 scalar_t__ __is_front_mergeable (struct extent_info*,struct extent_info*) ; 
 int /*<<< orphan*/  __release_extent_node (struct f2fs_sb_info*,struct extent_tree*,struct extent_node*) ; 
 int /*<<< orphan*/  __try_update_largest_extent (struct extent_tree*,struct extent_node*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct extent_node *__try_merge_extent_node(struct f2fs_sb_info *sbi,
				struct extent_tree *et, struct extent_info *ei,
				struct extent_node *prev_ex,
				struct extent_node *next_ex)
{
	struct extent_node *en = NULL;

	if (prev_ex && __is_back_mergeable(ei, &prev_ex->ei)) {
		prev_ex->ei.len += ei->len;
		ei = &prev_ex->ei;
		en = prev_ex;
	}

	if (next_ex && __is_front_mergeable(ei, &next_ex->ei)) {
		next_ex->ei.fofs = ei->fofs;
		next_ex->ei.blk = ei->blk;
		next_ex->ei.len += ei->len;
		if (en)
			__release_extent_node(sbi, et, prev_ex);

		en = next_ex;
	}

	if (!en)
		return NULL;

	__try_update_largest_extent(et, en);

	spin_lock(&sbi->extent_lock);
	if (!list_empty(&en->list)) {
		list_move_tail(&en->list, &sbi->extent_list);
		et->cached_en = en;
	}
	spin_unlock(&sbi->extent_lock);
	return en;
}