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
struct bq27xxx_device_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  bat; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  bq27xxx_list_lock ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ poll_interval ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

void bq27xxx_battery_teardown(struct bq27xxx_device_info *di)
{
	/*
	 * power_supply_unregister call bq27xxx_battery_get_property which
	 * call bq27xxx_battery_poll.
	 * Make sure that bq27xxx_battery_poll will not call
	 * schedule_delayed_work again after unregister (which cause OOPS).
	 */
	poll_interval = 0;

	cancel_delayed_work_sync(&di->work);

	power_supply_unregister(di->bat);

	mutex_lock(&bq27xxx_list_lock);
	list_del(&di->list);
	mutex_unlock(&bq27xxx_list_lock);

	mutex_destroy(&di->lock);
}