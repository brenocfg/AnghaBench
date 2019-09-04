#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int dummy; } ;
struct da9062_watchdog {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9062AA_CONTROL_D ; 
 int /*<<< orphan*/  DA9062AA_TWDSCALE_MASK ; 
 int /*<<< orphan*/  DA9062_TWDSCALE_DISABLE ; 
 int da9062_reset_watchdog_timer (struct da9062_watchdog*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9062_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int da9062_wdt_stop(struct watchdog_device *wdd)
{
	struct da9062_watchdog *wdt = watchdog_get_drvdata(wdd);
	int ret;

	ret = da9062_reset_watchdog_timer(wdt);
	if (ret) {
		dev_err(wdt->hw->dev, "Failed to ping the watchdog (err = %d)\n",
			ret);
		return ret;
	}

	ret = regmap_update_bits(wdt->hw->regmap,
				 DA9062AA_CONTROL_D,
				 DA9062AA_TWDSCALE_MASK,
				 DA9062_TWDSCALE_DISABLE);
	if (ret)
		dev_err(wdt->hw->dev, "Watchdog failed to stop (err = %d)\n",
			ret);

	return ret;
}