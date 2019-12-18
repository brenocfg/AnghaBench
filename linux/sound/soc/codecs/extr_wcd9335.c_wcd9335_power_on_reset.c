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
struct wcd9335_codec {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supplies; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9335_MAX_SUPPLY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wcd9335_power_on_reset(struct wcd9335_codec *wcd)
{
	struct device *dev = wcd->dev;
	int ret;

	ret = regulator_bulk_enable(WCD9335_MAX_SUPPLY, wcd->supplies);
	if (ret) {
		dev_err(dev, "Failed to get supplies: err = %d\n", ret);
		return ret;
	}

	/*
	 * For WCD9335, it takes about 600us for the Vout_A and
	 * Vout_D to be ready after BUCK_SIDO is powered up.
	 * SYS_RST_N shouldn't be pulled high during this time
	 * Toggle the reset line to make sure the reset pulse is
	 * correctly applied
	 */
	usleep_range(600, 650);

	gpio_direction_output(wcd->reset_gpio, 0);
	msleep(20);
	gpio_set_value(wcd->reset_gpio, 1);
	msleep(20);

	return 0;
}