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
struct i2c_client {int dummy; } ;
struct bq27xxx_device_info {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  battery_id ; 
 int /*<<< orphan*/  battery_mutex ; 
 int /*<<< orphan*/  bq27xxx_battery_teardown (struct bq27xxx_device_info*) ; 
 struct bq27xxx_device_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bq27xxx_battery_i2c_remove(struct i2c_client *client)
{
	struct bq27xxx_device_info *di = i2c_get_clientdata(client);

	bq27xxx_battery_teardown(di);

	mutex_lock(&battery_mutex);
	idr_remove(&battery_id, di->id);
	mutex_unlock(&battery_mutex);

	return 0;
}