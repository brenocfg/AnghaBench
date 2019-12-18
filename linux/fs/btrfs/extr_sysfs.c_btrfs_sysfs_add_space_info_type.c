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
struct btrfs_space_info {int /*<<< orphan*/  kobj; int /*<<< orphan*/  flags; } ;
struct btrfs_fs_info {int /*<<< orphan*/  space_info_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_name (int /*<<< orphan*/ ) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_info_ktype ; 

int btrfs_sysfs_add_space_info_type(struct btrfs_fs_info *fs_info,
				    struct btrfs_space_info *space_info)
{
	int ret;

	ret = kobject_init_and_add(&space_info->kobj, &space_info_ktype,
				   fs_info->space_info_kobj, "%s",
				   alloc_name(space_info->flags));
	if (ret) {
		kobject_put(&space_info->kobj);
		return ret;
	}

	return 0;
}