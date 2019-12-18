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
struct raid_kobject {int /*<<< orphan*/  kobj; int /*<<< orphan*/  flags; } ;
struct btrfs_space_info {int /*<<< orphan*/ ** block_group_kobjs; int /*<<< orphan*/  kobj; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  flags; struct btrfs_fs_info* fs_info; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int btrfs_bg_flags_to_raid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_bg_type_to_raid_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_raid_ktype ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*) ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct raid_kobject* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_nofs_restore (unsigned int) ; 
 unsigned int memalloc_nofs_save () ; 

void btrfs_sysfs_add_block_group_type(struct btrfs_block_group_cache *cache)
{
	struct btrfs_fs_info *fs_info = cache->fs_info;
	struct btrfs_space_info *space_info = cache->space_info;
	struct raid_kobject *rkobj;
	const int index = btrfs_bg_flags_to_raid_index(cache->flags);
	unsigned int nofs_flag;
	int ret;

	/*
	 * Setup a NOFS context because kobject_add(), deep in its call chain,
	 * does GFP_KERNEL allocations, and we are often called in a context
	 * where if reclaim is triggered we can deadlock (we are either holding
	 * a transaction handle or some lock required for a transaction
	 * commit).
	 */
	nofs_flag = memalloc_nofs_save();

	rkobj = kzalloc(sizeof(*rkobj), GFP_NOFS);
	if (!rkobj) {
		memalloc_nofs_restore(nofs_flag);
		btrfs_warn(cache->fs_info,
				"couldn't alloc memory for raid level kobject");
		return;
	}

	rkobj->flags = cache->flags;
	kobject_init(&rkobj->kobj, &btrfs_raid_ktype);
	ret = kobject_add(&rkobj->kobj, &space_info->kobj, "%s",
			  btrfs_bg_type_to_raid_name(rkobj->flags));
	memalloc_nofs_restore(nofs_flag);
	if (ret) {
		kobject_put(&rkobj->kobj);
		btrfs_warn(fs_info,
			"failed to add kobject for block cache, ignoring");
		return;
	}

	space_info->block_group_kobjs[index] = &rkobj->kobj;
}