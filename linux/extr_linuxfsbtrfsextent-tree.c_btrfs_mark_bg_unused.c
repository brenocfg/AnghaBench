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
struct btrfs_fs_info {int /*<<< orphan*/  unused_bgs_lock; int /*<<< orphan*/  unused_bgs; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  bg_list; struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_get_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_add_unused_block_group (struct btrfs_block_group_cache*) ; 

void btrfs_mark_bg_unused(struct btrfs_block_group_cache *bg)
{
	struct btrfs_fs_info *fs_info = bg->fs_info;

	spin_lock(&fs_info->unused_bgs_lock);
	if (list_empty(&bg->bg_list)) {
		btrfs_get_block_group(bg);
		trace_btrfs_add_unused_block_group(bg);
		list_add_tail(&bg->bg_list, &fs_info->unused_bgs);
	}
	spin_unlock(&fs_info->unused_bgs_lock);
}