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
struct device {int dummy; } ;
struct atmdev_ops {int dummy; } ;
struct atm_dev {int number; unsigned long flags; unsigned long stats; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  refcnt; struct atmdev_ops const* ops; } ;

/* Variables and functions */
 struct atm_dev* __alloc_atm_dev (char const*) ; 
 struct atm_dev* __atm_dev_lookup (int) ; 
 int /*<<< orphan*/  atm_dev_mutex ; 
 int /*<<< orphan*/  atm_dev_put (struct atm_dev*) ; 
 int /*<<< orphan*/  atm_devs ; 
 int /*<<< orphan*/  atm_proc_dev_deregister (struct atm_dev*) ; 
 scalar_t__ atm_proc_dev_register (struct atm_dev*) ; 
 scalar_t__ atm_register_sysfs (struct atm_dev*,struct device*) ; 
 int /*<<< orphan*/  kfree (struct atm_dev*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct atm_dev *atm_dev_register(const char *type, struct device *parent,
				 const struct atmdev_ops *ops, int number,
				 unsigned long *flags)
{
	struct atm_dev *dev, *inuse;

	dev = __alloc_atm_dev(type);
	if (!dev) {
		pr_err("no space for dev %s\n", type);
		return NULL;
	}
	mutex_lock(&atm_dev_mutex);
	if (number != -1) {
		inuse = __atm_dev_lookup(number);
		if (inuse) {
			atm_dev_put(inuse);
			mutex_unlock(&atm_dev_mutex);
			kfree(dev);
			return NULL;
		}
		dev->number = number;
	} else {
		dev->number = 0;
		while ((inuse = __atm_dev_lookup(dev->number))) {
			atm_dev_put(inuse);
			dev->number++;
		}
	}

	dev->ops = ops;
	if (flags)
		dev->flags = *flags;
	else
		memset(&dev->flags, 0, sizeof(dev->flags));
	memset(&dev->stats, 0, sizeof(dev->stats));
	refcount_set(&dev->refcnt, 1);

	if (atm_proc_dev_register(dev) < 0) {
		pr_err("atm_proc_dev_register failed for dev %s\n", type);
		goto out_fail;
	}

	if (atm_register_sysfs(dev, parent) < 0) {
		pr_err("atm_register_sysfs failed for dev %s\n", type);
		atm_proc_dev_deregister(dev);
		goto out_fail;
	}

	list_add_tail(&dev->dev_list, &atm_devs);

out:
	mutex_unlock(&atm_dev_mutex);
	return dev;

out_fail:
	kfree(dev);
	dev = NULL;
	goto out;
}