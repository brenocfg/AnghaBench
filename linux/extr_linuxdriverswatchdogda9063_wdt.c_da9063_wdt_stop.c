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
struct watchdog_device {int dummy; } ;
struct da9063 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int da9063_wdt_disable_timer (struct da9063*) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int) ; 
 struct da9063* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int da9063_wdt_stop(struct watchdog_device *wdd)
{
	struct da9063 *da9063 = watchdog_get_drvdata(wdd);
	int ret;

	ret = da9063_wdt_disable_timer(da9063);
	if (ret)
		dev_alert(da9063->dev, "Watchdog failed to stop (err = %d)\n",
			  ret);

	return ret;
}