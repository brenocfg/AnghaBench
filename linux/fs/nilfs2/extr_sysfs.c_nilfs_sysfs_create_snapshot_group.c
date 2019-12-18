#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct the_nilfs {int /*<<< orphan*/  ns_dev_kobj; TYPE_1__* ns_dev_subgroups; } ;
struct TYPE_4__ {int /*<<< orphan*/  kset; } ;
struct nilfs_root {int /*<<< orphan*/  cno; TYPE_2__ snapshot_kobj; int /*<<< orphan*/  snapshot_kobj_unregister; struct the_nilfs* nilfs; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {struct kobject sg_mounted_snapshots_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_CPTREE_CURRENT_CNO ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (TYPE_2__*,int /*<<< orphan*/ *,struct kobject*,char*,...) ; 
 int /*<<< orphan*/  nilfs_kset ; 
 int /*<<< orphan*/  nilfs_snapshot_ktype ; 

int nilfs_sysfs_create_snapshot_group(struct nilfs_root *root)
{
	struct the_nilfs *nilfs;
	struct kobject *parent;
	int err;

	nilfs = root->nilfs;
	parent = &nilfs->ns_dev_subgroups->sg_mounted_snapshots_kobj;
	root->snapshot_kobj.kset = nilfs_kset;
	init_completion(&root->snapshot_kobj_unregister);

	if (root->cno == NILFS_CPTREE_CURRENT_CNO) {
		err = kobject_init_and_add(&root->snapshot_kobj,
					    &nilfs_snapshot_ktype,
					    &nilfs->ns_dev_kobj,
					    "current_checkpoint");
	} else {
		err = kobject_init_and_add(&root->snapshot_kobj,
					    &nilfs_snapshot_ktype,
					    parent,
					    "%llu", root->cno);
	}

	if (err)
		return err;

	return 0;
}