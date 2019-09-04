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
 int BTRFS_BLOCK_GROUP_RAID0 ; 
 int BTRFS_BLOCK_GROUP_RAID1 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 int BTRFS_BLOCK_GROUP_RAID5 ; 
 int BTRFS_BLOCK_GROUP_RAID6 ; 

__attribute__((used)) static u64 get_profile_num_devs(struct btrfs_fs_info *fs_info, u64 type)
{
	u64 num_dev;

	if (type & (BTRFS_BLOCK_GROUP_RAID10 |
		    BTRFS_BLOCK_GROUP_RAID0 |
		    BTRFS_BLOCK_GROUP_RAID5 |
		    BTRFS_BLOCK_GROUP_RAID6))
		num_dev = fs_info->fs_devices->rw_devices;
	else if (type & BTRFS_BLOCK_GROUP_RAID1)
		num_dev = 2;
	else
		num_dev = 1;	/* DUP or single */

	return num_dev;
}