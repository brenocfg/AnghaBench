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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_WATCHDOG_STOP ; 
 int /*<<< orphan*/  dev_crit (struct device*,char*,int) ; 
 struct device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int wdt_command (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdt_stop(struct watchdog_device *wd)
{
	struct device *dev = watchdog_get_drvdata(wd);
	int ret;

	ret = wdt_command(SCU_WATCHDOG_STOP, NULL, 0);
	if (ret)
		dev_crit(dev, "Error stopping watchdog: %d\n", ret);

	return ret;
}