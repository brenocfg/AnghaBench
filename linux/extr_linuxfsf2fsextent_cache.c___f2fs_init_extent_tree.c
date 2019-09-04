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
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  extent_lock; int /*<<< orphan*/  extent_list; } ;
struct f2fs_extent {scalar_t__ len; } ;
struct extent_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  node_cnt; } ;
struct extent_node {int /*<<< orphan*/  list; } ;
struct extent_info {int dummy; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 struct extent_tree* __grab_extent_tree (struct inode*) ; 
 struct extent_node* __init_extent_tree (struct f2fs_sb_info*,struct extent_tree*,struct extent_info*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_may_extent_tree (struct inode*) ; 
 int /*<<< orphan*/  get_extent_info (struct extent_info*,struct f2fs_extent*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __f2fs_init_extent_tree(struct inode *inode, struct f2fs_extent *i_ext)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et;
	struct extent_node *en;
	struct extent_info ei;

	if (!f2fs_may_extent_tree(inode)) {
		/* drop largest extent */
		if (i_ext && i_ext->len) {
			i_ext->len = 0;
			return true;
		}
		return false;
	}

	et = __grab_extent_tree(inode);

	if (!i_ext || !i_ext->len)
		return false;

	get_extent_info(&ei, i_ext);

	write_lock(&et->lock);
	if (atomic_read(&et->node_cnt))
		goto out;

	en = __init_extent_tree(sbi, et, &ei);
	if (en) {
		spin_lock(&sbi->extent_lock);
		list_add_tail(&en->list, &sbi->extent_list);
		spin_unlock(&sbi->extent_lock);
	}
out:
	write_unlock(&et->lock);
	return false;
}