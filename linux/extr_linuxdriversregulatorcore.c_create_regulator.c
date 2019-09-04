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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct regulator_dev {int /*<<< orphan*/  debugfs; TYPE_1__ dev; int /*<<< orphan*/  consumer_list; } ;
struct regulator {int always_on; int /*<<< orphan*/  list; int /*<<< orphan*/  debugfs; TYPE_2__* voltage; int /*<<< orphan*/  uA_load; int /*<<< orphan*/ * supply_name; struct device* dev; struct regulator_dev* rdev; } ;
struct TYPE_6__ {char* name; } ;
struct device {TYPE_3__ kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_uV; int /*<<< orphan*/  min_uV; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PM_SUSPEND_ON ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_STATUS ; 
 int REG_STR_SIZE ; 
 scalar_t__ _regulator_is_enabled (struct regulator_dev*) ; 
 int /*<<< orphan*/  constraint_flags_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct regulator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct regulator*) ; 
 int /*<<< orphan*/ * kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 struct regulator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_dbg (struct regulator_dev*,char*,...) ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 
 int snprintf (char*,int,char*,char*,char const*) ; 
 int sysfs_create_link_nowarn (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 

__attribute__((used)) static struct regulator *create_regulator(struct regulator_dev *rdev,
					  struct device *dev,
					  const char *supply_name)
{
	struct regulator *regulator;
	char buf[REG_STR_SIZE];
	int err, size;

	regulator = kzalloc(sizeof(*regulator), GFP_KERNEL);
	if (regulator == NULL)
		return NULL;

	regulator_lock(rdev);
	regulator->rdev = rdev;
	list_add(&regulator->list, &rdev->consumer_list);

	if (dev) {
		regulator->dev = dev;

		/* Add a link to the device sysfs entry */
		size = snprintf(buf, REG_STR_SIZE, "%s-%s",
				dev->kobj.name, supply_name);
		if (size >= REG_STR_SIZE)
			goto overflow_err;

		regulator->supply_name = kstrdup(buf, GFP_KERNEL);
		if (regulator->supply_name == NULL)
			goto overflow_err;

		err = sysfs_create_link_nowarn(&rdev->dev.kobj, &dev->kobj,
					buf);
		if (err) {
			rdev_dbg(rdev, "could not add device link %s err %d\n",
				  dev->kobj.name, err);
			/* non-fatal */
		}
	} else {
		regulator->supply_name = kstrdup_const(supply_name, GFP_KERNEL);
		if (regulator->supply_name == NULL)
			goto overflow_err;
	}

	regulator->debugfs = debugfs_create_dir(regulator->supply_name,
						rdev->debugfs);
	if (!regulator->debugfs) {
		rdev_dbg(rdev, "Failed to create debugfs directory\n");
	} else {
		debugfs_create_u32("uA_load", 0444, regulator->debugfs,
				   &regulator->uA_load);
		debugfs_create_u32("min_uV", 0444, regulator->debugfs,
				   &regulator->voltage[PM_SUSPEND_ON].min_uV);
		debugfs_create_u32("max_uV", 0444, regulator->debugfs,
				   &regulator->voltage[PM_SUSPEND_ON].max_uV);
		debugfs_create_file("constraint_flags", 0444,
				    regulator->debugfs, regulator,
				    &constraint_flags_fops);
	}

	/*
	 * Check now if the regulator is an always on regulator - if
	 * it is then we don't need to do nearly so much work for
	 * enable/disable calls.
	 */
	if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_STATUS) &&
	    _regulator_is_enabled(rdev))
		regulator->always_on = true;

	regulator_unlock(rdev);
	return regulator;
overflow_err:
	list_del(&regulator->list);
	kfree(regulator);
	regulator_unlock(rdev);
	return NULL;
}