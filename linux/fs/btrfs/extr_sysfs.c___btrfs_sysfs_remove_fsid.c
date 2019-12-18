#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state_initialized; } ;
struct btrfs_fs_devices {int /*<<< orphan*/  kobj_unregister; TYPE_1__ fsid_kobj; TYPE_1__* device_dir_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (TYPE_1__*) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __btrfs_sysfs_remove_fsid(struct btrfs_fs_devices *fs_devs)
{
	if (fs_devs->device_dir_kobj) {
		kobject_del(fs_devs->device_dir_kobj);
		kobject_put(fs_devs->device_dir_kobj);
		fs_devs->device_dir_kobj = NULL;
	}

	if (fs_devs->fsid_kobj.state_initialized) {
		kobject_del(&fs_devs->fsid_kobj);
		kobject_put(&fs_devs->fsid_kobj);
		wait_for_completion(&fs_devs->kobj_unregister);
	}
}