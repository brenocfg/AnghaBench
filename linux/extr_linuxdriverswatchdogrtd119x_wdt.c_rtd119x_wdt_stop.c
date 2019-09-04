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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int dummy; } ;
struct rtd119x_watchdog_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RTD119X_TCWCR ; 
 int /*<<< orphan*/  RTD119X_TCWCR_WDEN_DISABLED ; 
 int /*<<< orphan*/  RTD119X_TCWCR_WDEN_MASK ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct rtd119x_watchdog_device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtd119x_wdt_stop(struct watchdog_device *wdev)
{
	struct rtd119x_watchdog_device *data = watchdog_get_drvdata(wdev);
	u32 val;

	val = readl_relaxed(data->base + RTD119X_TCWCR);
	val &= ~RTD119X_TCWCR_WDEN_MASK;
	val |= RTD119X_TCWCR_WDEN_DISABLED;
	writel(val, data->base + RTD119X_TCWCR);

	return 0;
}