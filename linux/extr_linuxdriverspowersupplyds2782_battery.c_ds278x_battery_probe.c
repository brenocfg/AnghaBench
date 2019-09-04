#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct ds278x_info* drv_data; } ;
struct i2c_device_id {size_t driver_data; } ;
struct TYPE_5__ {struct ds278x_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct ds278x_platform_data {int /*<<< orphan*/  rsns; } ;
struct TYPE_6__ {struct ds278x_info* name; } ;
struct ds278x_info {int id; int capacity; TYPE_2__ battery_desc; int /*<<< orphan*/  bat_work; int /*<<< orphan*/  battery; int /*<<< orphan*/  status; int /*<<< orphan*/ * ops; struct i2c_client* client; int /*<<< orphan*/  rsns; } ;

/* Variables and functions */
 size_t DS2786 ; 
 int /*<<< orphan*/  DS278x_DELAY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  battery_id ; 
 int /*<<< orphan*/  battery_lock ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ds278x_bat_work ; 
 int /*<<< orphan*/ * ds278x_ops ; 
 int /*<<< orphan*/  ds278x_power_supply_init (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ds278x_info*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 struct ds278x_info* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct ds278x_info*) ; 
 struct ds278x_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,TYPE_2__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds278x_battery_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct ds278x_platform_data *pdata = client->dev.platform_data;
	struct power_supply_config psy_cfg = {};
	struct ds278x_info *info;
	int ret;
	int num;

	/*
	 * ds2786 should have the sense resistor value set
	 * in the platform data
	 */
	if (id->driver_data == DS2786 && !pdata) {
		dev_err(&client->dev, "missing platform data for ds2786\n");
		return -EINVAL;
	}

	/* Get an ID for this battery */
	mutex_lock(&battery_lock);
	ret = idr_alloc(&battery_id, client, 0, 0, GFP_KERNEL);
	mutex_unlock(&battery_lock);
	if (ret < 0)
		goto fail_id;
	num = ret;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info) {
		ret = -ENOMEM;
		goto fail_info;
	}

	info->battery_desc.name = kasprintf(GFP_KERNEL, "%s-%d",
					    client->name, num);
	if (!info->battery_desc.name) {
		ret = -ENOMEM;
		goto fail_name;
	}

	if (id->driver_data == DS2786)
		info->rsns = pdata->rsns;

	i2c_set_clientdata(client, info);
	info->client = client;
	info->id = num;
	info->ops  = &ds278x_ops[id->driver_data];
	ds278x_power_supply_init(&info->battery_desc);
	psy_cfg.drv_data = info;

	info->capacity = 100;
	info->status = POWER_SUPPLY_STATUS_FULL;

	INIT_DELAYED_WORK(&info->bat_work, ds278x_bat_work);

	info->battery = power_supply_register(&client->dev,
					      &info->battery_desc, &psy_cfg);
	if (IS_ERR(info->battery)) {
		dev_err(&client->dev, "failed to register battery\n");
		ret = PTR_ERR(info->battery);
		goto fail_register;
	} else {
		schedule_delayed_work(&info->bat_work, DS278x_DELAY);
	}

	return 0;

fail_register:
	kfree(info->battery_desc.name);
fail_name:
	kfree(info);
fail_info:
	mutex_lock(&battery_lock);
	idr_remove(&battery_id, num);
	mutex_unlock(&battery_lock);
fail_id:
	return ret;
}