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
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct the_nilfs {int /*<<< orphan*/  ns_dev_subgroups; TYPE_1__ ns_dev_kobj; int /*<<< orphan*/  ns_dev_kobj_unregister; } ;
struct super_block {int /*<<< orphan*/  s_id; struct the_nilfs* s_fs_info; } ;
struct nilfs_sysfs_dev_subgroups {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_del (TYPE_1__*) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dev_ktype ; 
 int /*<<< orphan*/  nilfs_kset ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int nilfs_sysfs_create_checkpoints_group (struct the_nilfs*) ; 
 int nilfs_sysfs_create_mounted_snapshots_group (struct the_nilfs*) ; 
 int nilfs_sysfs_create_segctor_group (struct the_nilfs*) ; 
 int nilfs_sysfs_create_segments_group (struct the_nilfs*) ; 
 int nilfs_sysfs_create_superblock_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_checkpoints_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_mounted_snapshots_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_segments_group (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_superblock_group (struct the_nilfs*) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_sysfs_create_device_group(struct super_block *sb)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	size_t devgrp_size = sizeof(struct nilfs_sysfs_dev_subgroups);
	int err;

	nilfs->ns_dev_subgroups = kzalloc(devgrp_size, GFP_KERNEL);
	if (unlikely(!nilfs->ns_dev_subgroups)) {
		err = -ENOMEM;
		nilfs_msg(sb, KERN_ERR,
			  "unable to allocate memory for device group");
		goto failed_create_device_group;
	}

	nilfs->ns_dev_kobj.kset = nilfs_kset;
	init_completion(&nilfs->ns_dev_kobj_unregister);
	err = kobject_init_and_add(&nilfs->ns_dev_kobj, &nilfs_dev_ktype, NULL,
				    "%s", sb->s_id);
	if (err)
		goto free_dev_subgroups;

	err = nilfs_sysfs_create_mounted_snapshots_group(nilfs);
	if (err)
		goto cleanup_dev_kobject;

	err = nilfs_sysfs_create_checkpoints_group(nilfs);
	if (err)
		goto delete_mounted_snapshots_group;

	err = nilfs_sysfs_create_segments_group(nilfs);
	if (err)
		goto delete_checkpoints_group;

	err = nilfs_sysfs_create_superblock_group(nilfs);
	if (err)
		goto delete_segments_group;

	err = nilfs_sysfs_create_segctor_group(nilfs);
	if (err)
		goto delete_superblock_group;

	return 0;

delete_superblock_group:
	nilfs_sysfs_delete_superblock_group(nilfs);

delete_segments_group:
	nilfs_sysfs_delete_segments_group(nilfs);

delete_checkpoints_group:
	nilfs_sysfs_delete_checkpoints_group(nilfs);

delete_mounted_snapshots_group:
	nilfs_sysfs_delete_mounted_snapshots_group(nilfs);

cleanup_dev_kobject:
	kobject_del(&nilfs->ns_dev_kobj);

free_dev_subgroups:
	kfree(nilfs->ns_dev_subgroups);

failed_create_device_group:
	return err;
}