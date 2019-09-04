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
struct map_lookup {int type; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_RAID5 ; 
 int BTRFS_BLOCK_GROUP_RAID6 ; 

__attribute__((used)) static inline int nr_parity_stripes(struct map_lookup *map)
{
	if (map->type & BTRFS_BLOCK_GROUP_RAID5)
		return 1;
	else if (map->type & BTRFS_BLOCK_GROUP_RAID6)
		return 2;
	else
		return 0;
}