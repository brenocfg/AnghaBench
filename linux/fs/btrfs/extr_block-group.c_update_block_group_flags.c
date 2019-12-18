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
struct btrfs_fs_info {TYPE_1__* fs_devices; } ;
struct TYPE_2__ {int rw_devices; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DUP ; 
 int BTRFS_BLOCK_GROUP_RAID0 ; 
 int BTRFS_BLOCK_GROUP_RAID1 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 int BTRFS_BLOCK_GROUP_RAID1_MASK ; 
 int BTRFS_BLOCK_GROUP_RAID56_MASK ; 
 int extended_to_chunk (int) ; 
 int get_restripe_target (struct btrfs_fs_info*,int) ; 

__attribute__((used)) static u64 update_block_group_flags(struct btrfs_fs_info *fs_info, u64 flags)
{
	u64 num_devices;
	u64 stripped;

	/*
	 * if restripe for this chunk_type is on pick target profile and
	 * return, otherwise do the usual balance
	 */
	stripped = get_restripe_target(fs_info, flags);
	if (stripped)
		return extended_to_chunk(stripped);

	num_devices = fs_info->fs_devices->rw_devices;

	stripped = BTRFS_BLOCK_GROUP_RAID0 | BTRFS_BLOCK_GROUP_RAID56_MASK |
		BTRFS_BLOCK_GROUP_RAID1_MASK | BTRFS_BLOCK_GROUP_RAID10;

	if (num_devices == 1) {
		stripped |= BTRFS_BLOCK_GROUP_DUP;
		stripped = flags & ~stripped;

		/* turn raid0 into single device chunks */
		if (flags & BTRFS_BLOCK_GROUP_RAID0)
			return stripped;

		/* turn mirroring into duplication */
		if (flags & (BTRFS_BLOCK_GROUP_RAID1_MASK |
			     BTRFS_BLOCK_GROUP_RAID10))
			return stripped | BTRFS_BLOCK_GROUP_DUP;
	} else {
		/* they already had raid on here, just return */
		if (flags & stripped)
			return flags;

		stripped |= BTRFS_BLOCK_GROUP_DUP;
		stripped = flags & ~stripped;

		/* switch duplicated blocks with raid1 */
		if (flags & BTRFS_BLOCK_GROUP_DUP)
			return stripped | BTRFS_BLOCK_GROUP_RAID1;

		/* this is drive concat, leave it alone */
	}

	return flags;
}