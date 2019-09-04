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
struct atm_dev {int /*<<< orphan*/  dev_list; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_DF_REMOVED ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_dev_mutex ; 
 int /*<<< orphan*/  atm_dev_put (struct atm_dev*) ; 
 int /*<<< orphan*/  atm_dev_release_vccs (struct atm_dev*) ; 
 int /*<<< orphan*/  atm_proc_dev_deregister (struct atm_dev*) ; 
 int /*<<< orphan*/  atm_unregister_sysfs (struct atm_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void atm_dev_deregister(struct atm_dev *dev)
{
	BUG_ON(test_bit(ATM_DF_REMOVED, &dev->flags));
	set_bit(ATM_DF_REMOVED, &dev->flags);

	/*
	 * if we remove current device from atm_devs list, new device
	 * with same number can appear, such we need deregister proc,
	 * release async all vccs and remove them from vccs list too
	 */
	mutex_lock(&atm_dev_mutex);
	list_del(&dev->dev_list);
	mutex_unlock(&atm_dev_mutex);

	atm_dev_release_vccs(dev);
	atm_unregister_sysfs(dev);
	atm_proc_dev_deregister(dev);

	atm_dev_put(dev);
}