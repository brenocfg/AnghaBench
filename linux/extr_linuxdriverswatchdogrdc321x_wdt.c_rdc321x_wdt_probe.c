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
struct resource {int /*<<< orphan*/  start; } ;
struct rdc321x_wdt_pdata {int /*<<< orphan*/  sb_pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_ticks; int /*<<< orphan*/  timer; int /*<<< orphan*/  inuse; scalar_t__ queue; int /*<<< orphan*/  stop; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  sb_pdev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  RDC_WDT_RST ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rdc321x_wdt_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ rdc321x_wdt_device ; 
 int /*<<< orphan*/  rdc321x_wdt_misc ; 
 int /*<<< orphan*/  rdc321x_wdt_trigger ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdc321x_wdt_probe(struct platform_device *pdev)
{
	int err;
	struct resource *r;
	struct rdc321x_wdt_pdata *pdata;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(&pdev->dev, "no platform data supplied\n");
		return -ENODEV;
	}

	r = platform_get_resource_byname(pdev, IORESOURCE_IO, "wdt-reg");
	if (!r) {
		dev_err(&pdev->dev, "failed to get wdt-reg resource\n");
		return -ENODEV;
	}

	rdc321x_wdt_device.sb_pdev = pdata->sb_pdev;
	rdc321x_wdt_device.base_reg = r->start;

	err = misc_register(&rdc321x_wdt_misc);
	if (err < 0) {
		dev_err(&pdev->dev, "misc_register failed\n");
		return err;
	}

	spin_lock_init(&rdc321x_wdt_device.lock);

	/* Reset the watchdog */
	pci_write_config_dword(rdc321x_wdt_device.sb_pdev,
				rdc321x_wdt_device.base_reg, RDC_WDT_RST);

	init_completion(&rdc321x_wdt_device.stop);
	rdc321x_wdt_device.queue = 0;

	clear_bit(0, &rdc321x_wdt_device.inuse);

	timer_setup(&rdc321x_wdt_device.timer, rdc321x_wdt_trigger, 0);

	rdc321x_wdt_device.default_ticks = ticks;

	dev_info(&pdev->dev, "watchdog init success\n");

	return 0;
}