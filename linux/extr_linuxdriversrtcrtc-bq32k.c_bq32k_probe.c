#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct rtc_device {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ32K_MINUTES ; 
 int BQ32K_OF ; 
 int /*<<< orphan*/  BQ32K_SECONDS ; 
 int BQ32K_STOP ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_2__ bq32k_driver ; 
 int bq32k_read (struct device*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bq32k_rtc_ops ; 
 int bq32k_sysfs_register (struct device*) ; 
 int bq32k_write (struct device*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct rtc_device* devm_rtc_device_register (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rtc_device*) ; 
 int /*<<< orphan*/  trickle_charger_of_init (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq32k_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct rtc_device *rtc;
	uint8_t reg;
	int error;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	/* Check Oscillator Stop flag */
	error = bq32k_read(dev, &reg, BQ32K_SECONDS, 1);
	if (!error && (reg & BQ32K_STOP)) {
		dev_warn(dev, "Oscillator was halted. Restarting...\n");
		reg &= ~BQ32K_STOP;
		error = bq32k_write(dev, &reg, BQ32K_SECONDS, 1);
	}
	if (error)
		return error;

	/* Check Oscillator Failure flag */
	error = bq32k_read(dev, &reg, BQ32K_MINUTES, 1);
	if (error)
		return error;
	if (reg & BQ32K_OF)
		dev_warn(dev, "Oscillator Failure. Check RTC battery.\n");

	if (client->dev.of_node)
		trickle_charger_of_init(dev, client->dev.of_node);

	rtc = devm_rtc_device_register(&client->dev, bq32k_driver.driver.name,
						&bq32k_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	error = bq32k_sysfs_register(&client->dev);
	if (error) {
		dev_err(&client->dev,
			"Unable to create sysfs entries for rtc bq32000\n");
		return error;
	}


	i2c_set_clientdata(client, rtc);

	return 0;
}