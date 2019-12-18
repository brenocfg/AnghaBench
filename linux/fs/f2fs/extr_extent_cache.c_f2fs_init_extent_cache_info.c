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
struct f2fs_sb_info {int /*<<< orphan*/  total_ext_node; int /*<<< orphan*/  total_zombie_tree; int /*<<< orphan*/  zombie_list; int /*<<< orphan*/  total_ext_tree; int /*<<< orphan*/  extent_lock; int /*<<< orphan*/  extent_list; int /*<<< orphan*/  extent_tree_lock; int /*<<< orphan*/  extent_tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void f2fs_init_extent_cache_info(struct f2fs_sb_info *sbi)
{
	INIT_RADIX_TREE(&sbi->extent_tree_root, GFP_NOIO);
	mutex_init(&sbi->extent_tree_lock);
	INIT_LIST_HEAD(&sbi->extent_list);
	spin_lock_init(&sbi->extent_lock);
	atomic_set(&sbi->total_ext_tree, 0);
	INIT_LIST_HEAD(&sbi->zombie_list);
	atomic_set(&sbi->total_zombie_tree, 0);
	atomic_set(&sbi->total_ext_node, 0);
}