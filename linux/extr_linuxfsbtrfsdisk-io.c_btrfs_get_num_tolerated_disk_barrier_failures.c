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
typedef  int u64 ;
struct TYPE_2__ {int bg_flag; int /*<<< orphan*/  tolerated_failures; } ;

/* Variables and functions */
 int BTRFS_AVAIL_ALLOC_BIT_SINGLE ; 
 int BTRFS_BLOCK_GROUP_PROFILE_MASK ; 
 int BTRFS_NR_RAID_TYPES ; 
 size_t BTRFS_RAID_SINGLE ; 
 int INT_MAX ; 
 TYPE_1__* btrfs_raid_array ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

int btrfs_get_num_tolerated_disk_barrier_failures(u64 flags)
{
	int raid_type;
	int min_tolerated = INT_MAX;

	if ((flags & BTRFS_BLOCK_GROUP_PROFILE_MASK) == 0 ||
	    (flags & BTRFS_AVAIL_ALLOC_BIT_SINGLE))
		min_tolerated = min(min_tolerated,
				    btrfs_raid_array[BTRFS_RAID_SINGLE].
				    tolerated_failures);

	for (raid_type = 0; raid_type < BTRFS_NR_RAID_TYPES; raid_type++) {
		if (raid_type == BTRFS_RAID_SINGLE)
			continue;
		if (!(flags & btrfs_raid_array[raid_type].bg_flag))
			continue;
		min_tolerated = min(min_tolerated,
				    btrfs_raid_array[raid_type].
				    tolerated_failures);
	}

	if (min_tolerated == INT_MAX) {
		pr_warn("BTRFS: unknown raid flag: %llu", flags);
		min_tolerated = 0;
	}

	return min_tolerated;
}