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
typedef  int u64 ;
struct btrfs_fs_info {int /*<<< orphan*/  balance_lock; TYPE_1__* fs_devices; } ;
struct TYPE_4__ {int devs_min; int bg_flag; } ;
struct TYPE_3__ {int rw_devices; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_PROFILE_MASK ; 
 int BTRFS_BLOCK_GROUP_RAID0 ; 
 int BTRFS_BLOCK_GROUP_RAID1 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 int BTRFS_BLOCK_GROUP_RAID5 ; 
 int BTRFS_BLOCK_GROUP_RAID6 ; 
 int BTRFS_EXTENDED_PROFILE_MASK ; 
 int BTRFS_NR_RAID_TYPES ; 
 TYPE_2__* btrfs_raid_array ; 
 int extended_to_chunk (int) ; 
 int get_restripe_target (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 btrfs_reduce_alloc_profile(struct btrfs_fs_info *fs_info, u64 flags)
{
	u64 num_devices = fs_info->fs_devices->rw_devices;
	u64 target;
	u64 raid_type;
	u64 allowed = 0;

	/*
	 * See if restripe for this chunk_type is in progress, if so try to
	 * reduce to the target profile
	 */
	spin_lock(&fs_info->balance_lock);
	target = get_restripe_target(fs_info, flags);
	if (target) {
		/* Pick target profile only if it's already available */
		if ((flags & target) & BTRFS_EXTENDED_PROFILE_MASK) {
			spin_unlock(&fs_info->balance_lock);
			return extended_to_chunk(target);
		}
	}
	spin_unlock(&fs_info->balance_lock);

	/* First, mask out the RAID levels which aren't possible */
	for (raid_type = 0; raid_type < BTRFS_NR_RAID_TYPES; raid_type++) {
		if (num_devices >= btrfs_raid_array[raid_type].devs_min)
			allowed |= btrfs_raid_array[raid_type].bg_flag;
	}
	allowed &= flags;

	if (allowed & BTRFS_BLOCK_GROUP_RAID6)
		allowed = BTRFS_BLOCK_GROUP_RAID6;
	else if (allowed & BTRFS_BLOCK_GROUP_RAID5)
		allowed = BTRFS_BLOCK_GROUP_RAID5;
	else if (allowed & BTRFS_BLOCK_GROUP_RAID10)
		allowed = BTRFS_BLOCK_GROUP_RAID10;
	else if (allowed & BTRFS_BLOCK_GROUP_RAID1)
		allowed = BTRFS_BLOCK_GROUP_RAID1;
	else if (allowed & BTRFS_BLOCK_GROUP_RAID0)
		allowed = BTRFS_BLOCK_GROUP_RAID0;

	flags &= ~BTRFS_BLOCK_GROUP_PROFILE_MASK;

	return extended_to_chunk(flags | allowed);
}