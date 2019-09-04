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
struct kobject {int /*<<< orphan*/  kset; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_kobj; } ;
struct exofs_dev {int /*<<< orphan*/  did; struct kobject ed_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exofs_kset ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odev_ktype ; 

int exofs_sysfs_odev_add(struct exofs_dev *edev, struct exofs_sb_info *sbi)
{
	struct kobject *d_kobj;
	int retval = 0;

	/* create osd device group which contains following attributes
	 * osdname, systemid & uri
	 */
	d_kobj = &edev->ed_kobj;
	d_kobj->kset = exofs_kset;
	retval = kobject_init_and_add(d_kobj, &odev_ktype,
			&sbi->s_kobj, "dev%u", edev->did);
	if (retval) {
		EXOFS_ERR("ERROR: Failed to create sysfs entry for "
				"device dev%u\n", edev->did);
		return retval;
	}
	return 0;
}