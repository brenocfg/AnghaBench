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
struct rb_node {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  extent_lock; int /*<<< orphan*/  extent_list; } ;
struct extent_tree {struct extent_node* cached_en; int /*<<< orphan*/  root; } ;
struct extent_node {int /*<<< orphan*/  list; } ;
struct extent_info {int /*<<< orphan*/  fofs; } ;

/* Variables and functions */
 struct extent_node* __attach_extent_node (struct f2fs_sb_info*,struct extent_tree*,struct extent_info*,struct rb_node*,struct rb_node**,int) ; 
 int /*<<< orphan*/  __try_update_largest_extent (struct extent_tree*,struct extent_node*) ; 
 struct rb_node** f2fs_lookup_rb_tree_for_insert (struct f2fs_sb_info*,int /*<<< orphan*/ *,struct rb_node**,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct extent_node *__insert_extent_tree(struct f2fs_sb_info *sbi,
				struct extent_tree *et, struct extent_info *ei,
				struct rb_node **insert_p,
				struct rb_node *insert_parent,
				bool leftmost)
{
	struct rb_node **p;
	struct rb_node *parent = NULL;
	struct extent_node *en = NULL;

	if (insert_p && insert_parent) {
		parent = insert_parent;
		p = insert_p;
		goto do_insert;
	}

	leftmost = true;

	p = f2fs_lookup_rb_tree_for_insert(sbi, &et->root, &parent,
						ei->fofs, &leftmost);
do_insert:
	en = __attach_extent_node(sbi, et, ei, parent, p, leftmost);
	if (!en)
		return NULL;

	__try_update_largest_extent(et, en);

	/* update in global extent list */
	spin_lock(&sbi->extent_lock);
	list_add_tail(&en->list, &sbi->extent_list);
	et->cached_en = en;
	spin_unlock(&sbi->extent_lock);
	return en;
}