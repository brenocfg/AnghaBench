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
struct raid_kobject {int /*<<< orphan*/  kobj; int /*<<< orphan*/  list; int /*<<< orphan*/  flags; } ;
struct btrfs_space_info {int /*<<< orphan*/ ** block_group_kobjs; int /*<<< orphan*/  groups_sem; int /*<<< orphan*/ * block_groups; } ;
struct btrfs_fs_info {int /*<<< orphan*/  pending_raid_kobjs_lock; int /*<<< orphan*/  pending_raid_kobjs; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  flags; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  list; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int btrfs_bg_flags_to_raid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_raid_ktype ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct raid_kobject* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void link_block_group(struct btrfs_block_group_cache *cache)
{
	struct btrfs_space_info *space_info = cache->space_info;
	struct btrfs_fs_info *fs_info = cache->fs_info;
	int index = btrfs_bg_flags_to_raid_index(cache->flags);
	bool first = false;

	down_write(&space_info->groups_sem);
	if (list_empty(&space_info->block_groups[index]))
		first = true;
	list_add_tail(&cache->list, &space_info->block_groups[index]);
	up_write(&space_info->groups_sem);

	if (first) {
		struct raid_kobject *rkobj = kzalloc(sizeof(*rkobj), GFP_NOFS);
		if (!rkobj) {
			btrfs_warn(cache->fs_info,
				"couldn't alloc memory for raid level kobject");
			return;
		}
		rkobj->flags = cache->flags;
		kobject_init(&rkobj->kobj, &btrfs_raid_ktype);

		spin_lock(&fs_info->pending_raid_kobjs_lock);
		list_add_tail(&rkobj->list, &fs_info->pending_raid_kobjs);
		spin_unlock(&fs_info->pending_raid_kobjs_lock);
		space_info->block_group_kobjs[index] = &rkobj->kobj;
	}
}