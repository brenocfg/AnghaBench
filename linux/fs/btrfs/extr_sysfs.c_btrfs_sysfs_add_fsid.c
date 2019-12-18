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
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct btrfs_fs_devices {TYPE_1__ fsid_kobj; int /*<<< orphan*/  fsid; int /*<<< orphan*/  kobj_unregister; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_kset ; 
 int /*<<< orphan*/  btrfs_ktype ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,struct kobject*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 

int btrfs_sysfs_add_fsid(struct btrfs_fs_devices *fs_devs,
				struct kobject *parent)
{
	int error;

	init_completion(&fs_devs->kobj_unregister);
	fs_devs->fsid_kobj.kset = btrfs_kset;
	error = kobject_init_and_add(&fs_devs->fsid_kobj,
				&btrfs_ktype, parent, "%pU", fs_devs->fsid);
	if (error) {
		kobject_put(&fs_devs->fsid_kobj);
		return error;
	}

	return 0;
}