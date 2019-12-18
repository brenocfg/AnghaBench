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
struct f2fs_sb_info {int /*<<< orphan*/  extent_lock; } ;
struct extent_tree {int dummy; } ;
struct extent_node {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __detach_extent_node (struct f2fs_sb_info*,struct extent_tree*,struct extent_node*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __release_extent_node(struct f2fs_sb_info *sbi,
			struct extent_tree *et, struct extent_node *en)
{
	spin_lock(&sbi->extent_lock);
	f2fs_bug_on(sbi, list_empty(&en->list));
	list_del_init(&en->list);
	spin_unlock(&sbi->extent_lock);

	__detach_extent_node(sbi, et, en);
}