#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lp855x {int /*<<< orphan*/  bl; TYPE_1__* dev; int /*<<< orphan*/ * enable; int /*<<< orphan*/ * supply; int /*<<< orphan*/  mode; TYPE_4__* pdata; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  chipname; struct i2c_client* client; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_8__ {scalar_t__ period_ns; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PWM_BASED ; 
 int /*<<< orphan*/  REGISTER_BASED ; 
 int /*<<< orphan*/  backlight_update_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 TYPE_4__* dev_get_platdata (TYPE_1__*) ; 
 struct lp855x* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lp855x*) ; 
 int /*<<< orphan*/  lp855x_attr_group ; 
 int lp855x_backlight_register (struct lp855x*) ; 
 int lp855x_configure (struct lp855x*) ; 
 int lp855x_parse_dt (struct lp855x*) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lp855x_probe(struct i2c_client *cl, const struct i2c_device_id *id)
{
	struct lp855x *lp;
	int ret;

	if (!i2c_check_functionality(cl->adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EIO;

	lp = devm_kzalloc(&cl->dev, sizeof(struct lp855x), GFP_KERNEL);
	if (!lp)
		return -ENOMEM;

	lp->client = cl;
	lp->dev = &cl->dev;
	lp->chipname = id->name;
	lp->chip_id = id->driver_data;
	lp->pdata = dev_get_platdata(&cl->dev);

	if (!lp->pdata) {
		ret = lp855x_parse_dt(lp);
		if (ret < 0)
			return ret;
	}

	if (lp->pdata->period_ns > 0)
		lp->mode = PWM_BASED;
	else
		lp->mode = REGISTER_BASED;

	lp->supply = devm_regulator_get(lp->dev, "power");
	if (IS_ERR(lp->supply)) {
		if (PTR_ERR(lp->supply) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		lp->supply = NULL;
	}

	lp->enable = devm_regulator_get_optional(lp->dev, "enable");
	if (IS_ERR(lp->enable)) {
		ret = PTR_ERR(lp->enable);
		if (ret == -ENODEV) {
			lp->enable = NULL;
		} else {
			if (ret != -EPROBE_DEFER)
				dev_err(lp->dev, "error getting enable regulator: %d\n",
					ret);
			return ret;
		}
	}

	if (lp->supply) {
		ret = regulator_enable(lp->supply);
		if (ret < 0) {
			dev_err(&cl->dev, "failed to enable supply: %d\n", ret);
			return ret;
		}
	}

	if (lp->enable) {
		ret = regulator_enable(lp->enable);
		if (ret < 0) {
			dev_err(lp->dev, "failed to enable vddio: %d\n", ret);
			return ret;
		}

		/*
		 * LP8555 datasheet says t_RESPONSE (time between VDDIO and
		 * I2C) is 1ms.
		 */
		usleep_range(1000, 2000);
	}

	i2c_set_clientdata(cl, lp);

	ret = lp855x_configure(lp);
	if (ret) {
		dev_err(lp->dev, "device config err: %d", ret);
		return ret;
	}

	ret = lp855x_backlight_register(lp);
	if (ret) {
		dev_err(lp->dev,
			"failed to register backlight. err: %d\n", ret);
		return ret;
	}

	ret = sysfs_create_group(&lp->dev->kobj, &lp855x_attr_group);
	if (ret) {
		dev_err(lp->dev, "failed to register sysfs. err: %d\n", ret);
		return ret;
	}

	backlight_update_status(lp->bl);
	return 0;
}