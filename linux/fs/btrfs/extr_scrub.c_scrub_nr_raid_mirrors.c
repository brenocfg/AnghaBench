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
struct btrfs_bio {int map_type; scalar_t__ num_stripes; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_RAID5 ; 
 int BTRFS_BLOCK_GROUP_RAID6 ; 

__attribute__((used)) static inline int scrub_nr_raid_mirrors(struct btrfs_bio *bbio)
{
	if (bbio->map_type & BTRFS_BLOCK_GROUP_RAID5)
		return 2;
	else if (bbio->map_type & BTRFS_BLOCK_GROUP_RAID6)
		return 3;
	else
		return (int)bbio->num_stripes;
}