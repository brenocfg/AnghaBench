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
struct TYPE_2__ {unsigned int timeout; } ;
struct rtd119x_watchdog_device {TYPE_1__ wdt_dev; scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ RTD119X_TCWOV ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct rtd119x_watchdog_device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int rtd119x_wdt_set_timeout(struct watchdog_device *wdev, unsigned int val)
{
	struct rtd119x_watchdog_device *data = watchdog_get_drvdata(wdev);

	writel(val * clk_get_rate(data->clk), data->base + RTD119X_TCWOV);

	data->wdt_dev.timeout = val;

	return 0;
}