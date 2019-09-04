#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  bootstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mt7621_wdt_base ; 
 int /*<<< orphan*/  mt7621_wdt_bootcause () ; 
 TYPE_1__ mt7621_wdt_dev ; 
 scalar_t__ mt7621_wdt_is_running (TYPE_1__*) ; 
 int /*<<< orphan*/  mt7621_wdt_reset ; 
 int /*<<< orphan*/  mt7621_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  mt7621_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7621_wdt_probe(struct platform_device *pdev)
{
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mt7621_wdt_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mt7621_wdt_base))
		return PTR_ERR(mt7621_wdt_base);

	mt7621_wdt_reset = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (!IS_ERR(mt7621_wdt_reset))
		reset_control_deassert(mt7621_wdt_reset);

	mt7621_wdt_dev.bootstatus = mt7621_wdt_bootcause();

	watchdog_init_timeout(&mt7621_wdt_dev, mt7621_wdt_dev.max_timeout,
			      &pdev->dev);
	watchdog_set_nowayout(&mt7621_wdt_dev, nowayout);
	if (mt7621_wdt_is_running(&mt7621_wdt_dev)) {
		/*
		 * Make sure to apply timeout from watchdog core, taking
		 * the prescaler of this driver here into account (the
		 * boot loader might be using a different prescaler).
		 *
		 * To avoid spurious resets because of different scaling,
		 * we first disable the watchdog, set the new prescaler
		 * and timeout, and then re-enable the watchdog.
		 */
		mt7621_wdt_stop(&mt7621_wdt_dev);
		mt7621_wdt_start(&mt7621_wdt_dev);
		set_bit(WDOG_HW_RUNNING, &mt7621_wdt_dev.status);
	}

	return devm_watchdog_register_device(&pdev->dev, &mt7621_wdt_dev);
}