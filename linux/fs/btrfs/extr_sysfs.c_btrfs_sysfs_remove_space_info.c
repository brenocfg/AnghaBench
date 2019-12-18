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
struct kobject {int dummy; } ;
struct btrfs_space_info {struct kobject kobj; struct kobject** block_group_kobjs; } ;

/* Variables and functions */
 int BTRFS_NR_RAID_TYPES ; 
 int /*<<< orphan*/  kobject_del (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 

void btrfs_sysfs_remove_space_info(struct btrfs_space_info *space_info)
{
	int i;

	for (i = 0; i < BTRFS_NR_RAID_TYPES; i++) {
		struct kobject *kobj;

		kobj = space_info->block_group_kobjs[i];
		space_info->block_group_kobjs[i] = NULL;
		if (kobj) {
			kobject_del(kobj);
			kobject_put(kobj);
		}
	}
	kobject_del(&space_info->kobj);
	kobject_put(&space_info->kobj);
}