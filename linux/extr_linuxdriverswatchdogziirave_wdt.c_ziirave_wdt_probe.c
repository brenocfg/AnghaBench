#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int min_timeout; int timeout; int /*<<< orphan*/  groups; int /*<<< orphan*/ * parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct ziirave_wdt_data {int reset_reason; TYPE_1__ wdd; int /*<<< orphan*/  bootloader_rev; int /*<<< orphan*/  firmware_rev; int /*<<< orphan*/  sysfs_mutex; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int ZIIRAVE_STATE_INITIAL ; 
 int /*<<< orphan*/  ZIIRAVE_TIMEOUT_MAX ; 
 int ZIIRAVE_TIMEOUT_MIN ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_BOOT_VER_MAJOR ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_FIRM_VER_MAJOR ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_RESET_REASON ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_STATE ; 
 int /*<<< orphan*/  ZIIRAVE_WDT_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct ziirave_wdt_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ziirave_wdt_data*) ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_timeout ; 
 int /*<<< orphan*/ * ziirave_reasons ; 
 int /*<<< orphan*/  ziirave_wdt_groups ; 
 int /*<<< orphan*/  ziirave_wdt_info ; 
 int ziirave_wdt_init_duration (struct i2c_client*) ; 
 int /*<<< orphan*/  ziirave_wdt_ops ; 
 int ziirave_wdt_revision (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ziirave_wdt_set_timeout (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ziirave_wdt_stop (TYPE_1__*) ; 

__attribute__((used)) static int ziirave_wdt_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	int ret;
	struct ziirave_wdt_data *w_priv;
	int val;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	w_priv = devm_kzalloc(&client->dev, sizeof(*w_priv), GFP_KERNEL);
	if (!w_priv)
		return -ENOMEM;

	mutex_init(&w_priv->sysfs_mutex);

	w_priv->wdd.info = &ziirave_wdt_info;
	w_priv->wdd.ops = &ziirave_wdt_ops;
	w_priv->wdd.min_timeout = ZIIRAVE_TIMEOUT_MIN;
	w_priv->wdd.max_timeout = ZIIRAVE_TIMEOUT_MAX;
	w_priv->wdd.parent = &client->dev;
	w_priv->wdd.groups = ziirave_wdt_groups;

	ret = watchdog_init_timeout(&w_priv->wdd, wdt_timeout, &client->dev);
	if (ret) {
		dev_info(&client->dev,
			 "Unable to select timeout value, using default\n");
	}

	/*
	 * The default value set in the watchdog should be perfectly valid, so
	 * pass that in if we haven't provided one via the module parameter or
	 * of property.
	 */
	if (w_priv->wdd.timeout == 0) {
		val = i2c_smbus_read_byte_data(client, ZIIRAVE_WDT_TIMEOUT);
		if (val < 0)
			return val;

		if (val < ZIIRAVE_TIMEOUT_MIN)
			return -ENODEV;

		w_priv->wdd.timeout = val;
	} else {
		ret = ziirave_wdt_set_timeout(&w_priv->wdd,
					      w_priv->wdd.timeout);
		if (ret)
			return ret;

		dev_info(&client->dev, "Timeout set to %ds.",
			 w_priv->wdd.timeout);
	}

	watchdog_set_nowayout(&w_priv->wdd, nowayout);

	i2c_set_clientdata(client, w_priv);

	/* If in unconfigured state, set to stopped */
	val = i2c_smbus_read_byte_data(client, ZIIRAVE_WDT_STATE);
	if (val < 0)
		return val;

	if (val == ZIIRAVE_STATE_INITIAL)
		ziirave_wdt_stop(&w_priv->wdd);

	ret = ziirave_wdt_init_duration(client);
	if (ret)
		return ret;

	ret = ziirave_wdt_revision(client, &w_priv->firmware_rev,
				   ZIIRAVE_WDT_FIRM_VER_MAJOR);
	if (ret)
		return ret;

	ret = ziirave_wdt_revision(client, &w_priv->bootloader_rev,
				   ZIIRAVE_WDT_BOOT_VER_MAJOR);
	if (ret)
		return ret;

	w_priv->reset_reason = i2c_smbus_read_byte_data(client,
						ZIIRAVE_WDT_RESET_REASON);
	if (w_priv->reset_reason < 0)
		return w_priv->reset_reason;

	if (w_priv->reset_reason >= ARRAY_SIZE(ziirave_reasons) ||
	    !ziirave_reasons[w_priv->reset_reason])
		return -ENODEV;

	ret = watchdog_register_device(&w_priv->wdd);

	return ret;
}