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
struct watchdog_device {unsigned int timeout; } ;
struct menf21bmc_wdt {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC_CMD_WD_TIME ; 
 int i2c_smbus_write_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct menf21bmc_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int
menf21bmc_wdt_settimeout(struct watchdog_device *wdt, unsigned int timeout)
{
	int ret;
	struct menf21bmc_wdt *drv_data = watchdog_get_drvdata(wdt);

	/*
	 *  BMC Watchdog does have a resolution of 100ms.
	 *  Watchdog API defines the timeout in seconds, so we have to
	 *  multiply the value.
	 */
	ret = i2c_smbus_write_word_data(drv_data->i2c_client,
					BMC_CMD_WD_TIME, timeout * 10);
	if (ret < 0)
		return ret;

	wdt->timeout = timeout;

	return 0;
}