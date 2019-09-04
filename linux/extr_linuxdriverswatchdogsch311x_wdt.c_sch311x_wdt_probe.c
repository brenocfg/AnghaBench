#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {int runtime_reg; int /*<<< orphan*/  boot_status; int /*<<< orphan*/  io_lock; } ;
struct TYPE_4__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EBUSY ; 
 int GP60 ; 
 int WATCHDOG_MINOR ; 
 int /*<<< orphan*/  WATCHDOG_TIMEOUT ; 
 int WDT_CFG ; 
 int WDT_CTRL ; 
 int WDT_TIME_OUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ sch311x_wdt_data ; 
 int /*<<< orphan*/  sch311x_wdt_get_status (int /*<<< orphan*/ *) ; 
 TYPE_1__ sch311x_wdt_miscdev ; 
 scalar_t__ sch311x_wdt_set_heartbeat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch311x_wdt_stop () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int sch311x_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int err;

	spin_lock_init(&sch311x_wdt_data.io_lock);

	if (!request_region(sch311x_wdt_data.runtime_reg + GP60, 1, DRV_NAME)) {
		dev_err(dev, "Failed to request region 0x%04x-0x%04x.\n",
			sch311x_wdt_data.runtime_reg + GP60,
			sch311x_wdt_data.runtime_reg + GP60);
		err = -EBUSY;
		goto exit;
	}

	if (!request_region(sch311x_wdt_data.runtime_reg + WDT_TIME_OUT, 4,
								DRV_NAME)) {
		dev_err(dev, "Failed to request region 0x%04x-0x%04x.\n",
			sch311x_wdt_data.runtime_reg + WDT_TIME_OUT,
			sch311x_wdt_data.runtime_reg + WDT_CTRL);
		err = -EBUSY;
		goto exit_release_region;
	}

	/* Make sure that the watchdog is not running */
	sch311x_wdt_stop();

	/* Disable keyboard and mouse interaction and interrupt */
	/* -- Watchdog timer configuration --
	 * Bit 0   Reserved
	 * Bit 1   Keyboard enable: 0* = No Reset, 1 = Reset WDT upon KBD Intr.
	 * Bit 2   Mouse enable: 0* = No Reset, 1 = Reset WDT upon Mouse Intr
	 * Bit 3   Reserved
	 * Bit 4-7 WDT Interrupt Mapping: (0000* = Disabled,
	 *            0001=IRQ1, 0010=(Invalid), 0011=IRQ3 to 1111=IRQ15)
	 */
	outb(0, sch311x_wdt_data.runtime_reg + WDT_CFG);

	/* Check that the heartbeat value is within it's range ;
	 * if not reset to the default */
	if (sch311x_wdt_set_heartbeat(timeout)) {
		sch311x_wdt_set_heartbeat(WATCHDOG_TIMEOUT);
		dev_info(dev, "timeout value must be 1<=x<=15300, using %d\n",
			timeout);
	}

	/* Get status at boot */
	sch311x_wdt_get_status(&sch311x_wdt_data.boot_status);

	sch311x_wdt_miscdev.parent = dev;

	err = misc_register(&sch311x_wdt_miscdev);
	if (err != 0) {
		dev_err(dev, "cannot register miscdev on minor=%d (err=%d)\n",
							WATCHDOG_MINOR, err);
		goto exit_release_region2;
	}

	dev_info(dev,
		"SMSC SCH311x WDT initialized. timeout=%d sec (nowayout=%d)\n",
		timeout, nowayout);

	return 0;

exit_release_region2:
	release_region(sch311x_wdt_data.runtime_reg + WDT_TIME_OUT, 4);
exit_release_region:
	release_region(sch311x_wdt_data.runtime_reg + GP60, 1);
	sch311x_wdt_data.runtime_reg = 0;
exit:
	return err;
}