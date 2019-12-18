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
struct f2fs_sb_info {int /*<<< orphan*/  total_ext_node; } ;
struct extent_tree {int /*<<< orphan*/  node_cnt; int /*<<< orphan*/  root; } ;
struct extent_info {int dummy; } ;
struct extent_node {int /*<<< orphan*/  rb_node; struct extent_tree* et; int /*<<< orphan*/  list; struct extent_info ei; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_node_slab ; 
 struct extent_node* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_insert_color_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 

__attribute__((used)) static struct extent_node *__attach_extent_node(struct f2fs_sb_info *sbi,
				struct extent_tree *et, struct extent_info *ei,
				struct rb_node *parent, struct rb_node **p,
				bool leftmost)
{
	struct extent_node *en;

	en = kmem_cache_alloc(extent_node_slab, GFP_ATOMIC);
	if (!en)
		return NULL;

	en->ei = *ei;
	INIT_LIST_HEAD(&en->list);
	en->et = et;

	rb_link_node(&en->rb_node, parent, p);
	rb_insert_color_cached(&en->rb_node, &et->root, leftmost);
	atomic_inc(&et->node_cnt);
	atomic_inc(&sbi->total_ext_node);
	return en;
}