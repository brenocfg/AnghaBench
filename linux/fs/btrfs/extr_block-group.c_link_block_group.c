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
struct btrfs_space_info {int /*<<< orphan*/  groups_sem; int /*<<< orphan*/ * block_groups; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int btrfs_bg_flags_to_raid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_sysfs_add_block_group_type (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void link_block_group(struct btrfs_block_group_cache *cache)
{
	struct btrfs_space_info *space_info = cache->space_info;
	int index = btrfs_bg_flags_to_raid_index(cache->flags);
	bool first = false;

	down_write(&space_info->groups_sem);
	if (list_empty(&space_info->block_groups[index]))
		first = true;
	list_add_tail(&cache->list, &space_info->block_groups[index]);
	up_write(&space_info->groups_sem);

	if (first)
		btrfs_sysfs_add_block_group_type(cache);
}