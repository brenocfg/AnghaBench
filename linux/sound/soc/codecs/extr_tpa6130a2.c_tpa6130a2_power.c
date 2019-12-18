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
struct tpa6130a2_data {scalar_t__ power_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  supply; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpa6130a2_power(struct tpa6130a2_data *data, bool enable)
{
	int ret = 0, ret2;

	if (enable) {
		ret = regulator_enable(data->supply);
		if (ret != 0) {
			dev_err(data->dev,
				"Failed to enable supply: %d\n", ret);
			return ret;
		}
		/* Power on */
		if (data->power_gpio >= 0)
			gpio_set_value(data->power_gpio, 1);

		/* Sync registers */
		regcache_cache_only(data->regmap, false);
		ret = regcache_sync(data->regmap);
		if (ret != 0) {
			dev_err(data->dev,
				"Failed to sync registers: %d\n", ret);
			regcache_cache_only(data->regmap, true);
			if (data->power_gpio >= 0)
				gpio_set_value(data->power_gpio, 0);
			ret2 = regulator_disable(data->supply);
			if (ret2 != 0)
				dev_err(data->dev,
					"Failed to disable supply: %d\n", ret2);
			return ret;
		}
	} else {
		/* Powered off device does not retain registers. While device
		 * is off, any register updates (i.e. volume changes) should
		 * happen in cache only.
		 */
		regcache_mark_dirty(data->regmap);
		regcache_cache_only(data->regmap, true);

		/* Power off */
		if (data->power_gpio >= 0)
			gpio_set_value(data->power_gpio, 0);

		ret = regulator_disable(data->supply);
		if (ret != 0) {
			dev_err(data->dev,
				"Failed to disable supply: %d\n", ret);
			return ret;
		}
	}

	return ret;
}