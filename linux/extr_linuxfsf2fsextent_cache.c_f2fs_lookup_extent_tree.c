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
struct rb_entry {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  extent_lock; int /*<<< orphan*/  extent_list; } ;
struct extent_info {scalar_t__ fofs; scalar_t__ len; } ;
struct extent_tree {int /*<<< orphan*/  lock; struct extent_node* cached_en; int /*<<< orphan*/  root; struct extent_info largest; } ;
struct extent_node {int /*<<< orphan*/  list; struct extent_info ei; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_2__ {struct extent_tree* extent_tree; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 scalar_t__ f2fs_lookup_rb_tree (int /*<<< orphan*/ *,struct rb_entry*,scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_inc_cached_node_hit (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  stat_inc_largest_node_hit (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  stat_inc_rbtree_node_hit (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  stat_inc_total_hit (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  trace_f2fs_lookup_extent_tree_end (struct inode*,scalar_t__,struct extent_info*) ; 
 int /*<<< orphan*/  trace_f2fs_lookup_extent_tree_start (struct inode*,scalar_t__) ; 

__attribute__((used)) static bool f2fs_lookup_extent_tree(struct inode *inode, pgoff_t pgofs,
							struct extent_info *ei)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et = F2FS_I(inode)->extent_tree;
	struct extent_node *en;
	bool ret = false;

	f2fs_bug_on(sbi, !et);

	trace_f2fs_lookup_extent_tree_start(inode, pgofs);

	read_lock(&et->lock);

	if (et->largest.fofs <= pgofs &&
			et->largest.fofs + et->largest.len > pgofs) {
		*ei = et->largest;
		ret = true;
		stat_inc_largest_node_hit(sbi);
		goto out;
	}

	en = (struct extent_node *)f2fs_lookup_rb_tree(&et->root,
				(struct rb_entry *)et->cached_en, pgofs);
	if (!en)
		goto out;

	if (en == et->cached_en)
		stat_inc_cached_node_hit(sbi);
	else
		stat_inc_rbtree_node_hit(sbi);

	*ei = en->ei;
	spin_lock(&sbi->extent_lock);
	if (!list_empty(&en->list)) {
		list_move_tail(&en->list, &sbi->extent_list);
		et->cached_en = en;
	}
	spin_unlock(&sbi->extent_lock);
	ret = true;
out:
	stat_inc_total_hit(sbi);
	read_unlock(&et->lock);

	trace_f2fs_lookup_extent_tree_end(inode, pgofs, ei);
	return ret;
}