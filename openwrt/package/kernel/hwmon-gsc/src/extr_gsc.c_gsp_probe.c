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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  name; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  attrs; } ;
struct gsp_data {int type; TYPE_1__ attrs; int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsp_attributes ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct gsp_data*) ; 
 int /*<<< orphan*/  kfree (struct gsp_data*) ; 
 struct gsp_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int gsp_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct gsp_data *data;
	int err;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WORD_DATA)) {
		err = -EOPNOTSUPP;
		goto exit;
	}

	if (!(data = kzalloc(sizeof(struct gsp_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);

	data->type = id->driver_data;

	switch (data->type) {
	case 0:
		data->attrs.attrs = gsp_attributes;
		break;
	}

	dev_info(&client->dev, "%s chip found\n", client->name);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &data->attrs)))
		goto exit_free;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	sysfs_remove_group(&client->dev.kobj, &data->attrs);
exit_free:
	kfree(data);
exit:
	return err;
}