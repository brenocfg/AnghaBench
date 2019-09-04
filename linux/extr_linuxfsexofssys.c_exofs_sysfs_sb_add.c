#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct kobject {TYPE_3__* kset; } ;
struct TYPE_4__ {int /*<<< orphan*/  partition; } ;
struct TYPE_5__ {TYPE_1__ obj; } ;
struct exofs_sb_info {struct kobject s_kobj; TYPE_2__ one_comp; } ;
struct exofs_dt_device_info {int /*<<< orphan*/  osdname; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* exofs_kset ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_ktype ; 

int exofs_sysfs_sb_add(struct exofs_sb_info *sbi,
		       struct exofs_dt_device_info *dt_dev)
{
	struct kobject *s_kobj;
	int retval = 0;
	uint64_t pid = sbi->one_comp.obj.partition;

	/* allocate new uuid dirent */
	s_kobj = &sbi->s_kobj;
	s_kobj->kset = exofs_kset;
	retval = kobject_init_and_add(s_kobj, &uuid_ktype,
			&exofs_kset->kobj,  "%s_%llx", dt_dev->osdname, pid);
	if (retval) {
		EXOFS_ERR("ERROR: Failed to create sysfs entry for "
			  "uuid-%s_%llx => %d\n", dt_dev->osdname, pid, retval);
		return -ENOMEM;
	}
	return 0;
}