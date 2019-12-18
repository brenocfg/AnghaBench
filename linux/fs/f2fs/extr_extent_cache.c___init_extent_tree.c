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
struct rb_node {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_3__ {struct rb_node* rb_node; } ;
struct TYPE_4__ {TYPE_1__ rb_root; } ;
struct extent_tree {struct extent_node* cached_en; int /*<<< orphan*/  largest; TYPE_2__ root; } ;
struct extent_node {int /*<<< orphan*/  ei; } ;
struct extent_info {int dummy; } ;

/* Variables and functions */
 struct extent_node* __attach_extent_node (struct f2fs_sb_info*,struct extent_tree*,struct extent_info*,int /*<<< orphan*/ *,struct rb_node**,int) ; 

__attribute__((used)) static struct extent_node *__init_extent_tree(struct f2fs_sb_info *sbi,
				struct extent_tree *et, struct extent_info *ei)
{
	struct rb_node **p = &et->root.rb_root.rb_node;
	struct extent_node *en;

	en = __attach_extent_node(sbi, et, ei, NULL, p, true);
	if (!en)
		return NULL;

	et->largest = en->ei;
	et->cached_en = en;
	return en;
}