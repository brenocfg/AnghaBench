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
typedef  enum btrfs_raid_types { ____Placeholder_btrfs_raid_types } btrfs_raid_types ;
struct TYPE_2__ {char const* raid_name; } ;

/* Variables and functions */
 int BTRFS_NR_RAID_TYPES ; 
 TYPE_1__* btrfs_raid_array ; 

const char *get_raid_name(enum btrfs_raid_types type)
{
	if (type >= BTRFS_NR_RAID_TYPES)
		return NULL;

	return btrfs_raid_array[type].raid_name;
}