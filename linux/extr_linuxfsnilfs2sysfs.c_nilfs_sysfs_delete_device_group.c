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
struct the_nilfs {int /*<<< orphan*/  ns_dev_subgroups; int /*<<< orphan*/  ns_dev_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_checkpoints_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_mounted_snapshots_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_segctor_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_segments_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_superblock_group (struct the_nilfs*) ; 

void nilfs_sysfs_delete_device_group(struct the_nilfs *nilfs)
{
	nilfs_sysfs_delete_mounted_snapshots_group(nilfs);
	nilfs_sysfs_delete_checkpoints_group(nilfs);
	nilfs_sysfs_delete_segments_group(nilfs);
	nilfs_sysfs_delete_superblock_group(nilfs);
	nilfs_sysfs_delete_segctor_group(nilfs);
	kobject_del(&nilfs->ns_dev_kobj);
	kfree(nilfs->ns_dev_subgroups);
}