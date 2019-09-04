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
struct rn5t618_wdt {TYPE_1__* rn5t618; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RN5T618_PWRIRQ ; 
 int /*<<< orphan*/  RN5T618_PWRIRQ_IR_WDOG ; 
 int /*<<< orphan*/  RN5T618_WATCHDOG ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct rn5t618_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int rn5t618_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct rn5t618_wdt *wdt = watchdog_get_drvdata(wdt_dev);
	unsigned int val;
	int ret;

	/* The counter is restarted after a R/W access to watchdog register */
	ret = regmap_read(wdt->rn5t618->regmap, RN5T618_WATCHDOG, &val);
	if (ret)
		return ret;

	ret = regmap_write(wdt->rn5t618->regmap, RN5T618_WATCHDOG, val);
	if (ret)
		return ret;

	/* Clear pending watchdog interrupt */
	return regmap_update_bits(wdt->rn5t618->regmap, RN5T618_PWRIRQ,
				  RN5T618_PWRIRQ_IR_WDOG, 0);
}