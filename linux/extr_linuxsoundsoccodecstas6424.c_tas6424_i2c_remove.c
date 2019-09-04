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
struct tas6424_data {int /*<<< orphan*/  supplies; scalar_t__ standby_gpio; int /*<<< orphan*/  fault_check_work; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tas6424_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas6424_i2c_remove(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct tas6424_data *tas6424 = dev_get_drvdata(dev);
	int ret;

	cancel_delayed_work_sync(&tas6424->fault_check_work);

	/* put the codec in stand-by */
	if (tas6424->standby_gpio)
		gpiod_set_value_cansleep(tas6424->standby_gpio, 1);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas6424->supplies),
				     tas6424->supplies);
	if (ret < 0) {
		dev_err(dev, "unable to disable supplies: %d\n", ret);
		return ret;
	}

	return 0;
}