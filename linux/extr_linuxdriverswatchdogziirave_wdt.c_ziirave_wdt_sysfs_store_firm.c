#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct ziirave_wdt_data {int /*<<< orphan*/  sysfs_mutex; TYPE_1__ wdd; TYPE_2__ firmware_rev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZIIRAVE_FW_NAME ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_FIRM_VER_MAJOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ziirave_wdt_data* i2c_get_clientdata (struct i2c_client*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_ihex_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int ziirave_firm_upload (TYPE_1__*,struct firmware const*) ; 
 int ziirave_wdt_revision (struct i2c_client*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ziirave_wdt_set_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ziirave_wdt_sysfs_store_firm(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev->parent);
	struct ziirave_wdt_data *w_priv = i2c_get_clientdata(client);
	const struct firmware *fw;
	int err;

	err = request_ihex_firmware(&fw, ZIIRAVE_FW_NAME, dev);
	if (err) {
		dev_err(&client->dev, "Failed to request ihex firmware\n");
		return err;
	}

	err = mutex_lock_interruptible(&w_priv->sysfs_mutex);
	if (err)
		goto release_firmware;

	err = ziirave_firm_upload(&w_priv->wdd, fw);
	if (err) {
		dev_err(&client->dev, "The firmware update failed: %d\n", err);
		goto unlock_mutex;
	}

	/* Update firmware version */
	err = ziirave_wdt_revision(client, &w_priv->firmware_rev,
				   ZIIRAVE_WDT_FIRM_VER_MAJOR);
	if (err) {
		dev_err(&client->dev, "Failed to read firmware version: %d\n",
			err);
		goto unlock_mutex;
	}

	dev_info(&client->dev, "Firmware updated to version 02.%02u.%02u\n",
		 w_priv->firmware_rev.major, w_priv->firmware_rev.minor);

	/* Restore the watchdog timeout */
	err = ziirave_wdt_set_timeout(&w_priv->wdd, w_priv->wdd.timeout);
	if (err)
		dev_err(&client->dev, "Failed to set timeout: %d\n", err);

unlock_mutex:
	mutex_unlock(&w_priv->sysfs_mutex);

release_firmware:
	release_firmware(fw);

	return err ? err : count;
}