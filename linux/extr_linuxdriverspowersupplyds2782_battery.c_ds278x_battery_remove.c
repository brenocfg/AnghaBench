#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct TYPE_2__ {struct ds278x_info* name; } ;
struct ds278x_info {int /*<<< orphan*/  bat_work; int /*<<< orphan*/  id; TYPE_1__ battery_desc; int /*<<< orphan*/  battery; } ;

/* Variables and functions */
 int /*<<< orphan*/  battery_id ; 
 int /*<<< orphan*/  battery_lock ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct ds278x_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ds278x_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds278x_battery_remove(struct i2c_client *client)
{
	struct ds278x_info *info = i2c_get_clientdata(client);

	power_supply_unregister(info->battery);
	kfree(info->battery_desc.name);

	mutex_lock(&battery_lock);
	idr_remove(&battery_id, info->id);
	mutex_unlock(&battery_lock);

	cancel_delayed_work(&info->bat_work);

	kfree(info);
	return 0;
}