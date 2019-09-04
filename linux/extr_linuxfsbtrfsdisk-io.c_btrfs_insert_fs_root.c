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
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {int /*<<< orphan*/  state; TYPE_1__ root_key; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fs_roots_radix_lock; int /*<<< orphan*/  fs_roots_radix; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_IN_RADIX ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct btrfs_root*) ; 
 int radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_insert_fs_root(struct btrfs_fs_info *fs_info,
			 struct btrfs_root *root)
{
	int ret;

	ret = radix_tree_preload(GFP_NOFS);
	if (ret)
		return ret;

	spin_lock(&fs_info->fs_roots_radix_lock);
	ret = radix_tree_insert(&fs_info->fs_roots_radix,
				(unsigned long)root->root_key.objectid,
				root);
	if (ret == 0)
		set_bit(BTRFS_ROOT_IN_RADIX, &root->state);
	spin_unlock(&fs_info->fs_roots_radix_lock);
	radix_tree_preload_end();

	return ret;
}