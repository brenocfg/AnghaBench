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
typedef  int u64 ;
struct btrfs_space_info {int flags; int /*<<< orphan*/  list; int /*<<< orphan*/  priority_tickets; int /*<<< orphan*/  tickets; int /*<<< orphan*/  ro_bgs; int /*<<< orphan*/  wait; int /*<<< orphan*/  force_alloc; int /*<<< orphan*/  lock; int /*<<< orphan*/  groups_sem; int /*<<< orphan*/ * block_groups; int /*<<< orphan*/  total_bytes_pinned; } ;
struct btrfs_fs_info {struct btrfs_space_info* data_sinfo; int /*<<< orphan*/  space_info; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DATA ; 
 int BTRFS_BLOCK_GROUP_TYPE_MASK ; 
 int BTRFS_NR_RAID_TYPES ; 
 int /*<<< orphan*/  CHUNK_ALLOC_NO_FORCE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int btrfs_sysfs_add_space_info_type (struct btrfs_fs_info*,struct btrfs_space_info*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_space_info*) ; 
 struct btrfs_space_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_space_info(struct btrfs_fs_info *info, u64 flags)
{

	struct btrfs_space_info *space_info;
	int i;
	int ret;

	space_info = kzalloc(sizeof(*space_info), GFP_NOFS);
	if (!space_info)
		return -ENOMEM;

	ret = percpu_counter_init(&space_info->total_bytes_pinned, 0,
				 GFP_KERNEL);
	if (ret) {
		kfree(space_info);
		return ret;
	}

	for (i = 0; i < BTRFS_NR_RAID_TYPES; i++)
		INIT_LIST_HEAD(&space_info->block_groups[i]);
	init_rwsem(&space_info->groups_sem);
	spin_lock_init(&space_info->lock);
	space_info->flags = flags & BTRFS_BLOCK_GROUP_TYPE_MASK;
	space_info->force_alloc = CHUNK_ALLOC_NO_FORCE;
	init_waitqueue_head(&space_info->wait);
	INIT_LIST_HEAD(&space_info->ro_bgs);
	INIT_LIST_HEAD(&space_info->tickets);
	INIT_LIST_HEAD(&space_info->priority_tickets);

	ret = btrfs_sysfs_add_space_info_type(info, space_info);
	if (ret)
		return ret;

	list_add_rcu(&space_info->list, &info->space_info);
	if (flags & BTRFS_BLOCK_GROUP_DATA)
		info->data_sinfo = space_info;

	return ret;
}