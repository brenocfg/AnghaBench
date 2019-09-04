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
struct watchdog_device {int /*<<< orphan*/  timeout; TYPE_1__* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct cdns_wdt {int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  ctrl_clksel; int /*<<< orphan*/  prescaler; int /*<<< orphan*/  rst; struct watchdog_device cdns_wdt_device; } ;

/* Variables and functions */
 unsigned long CDNS_WDT_CLK_75MHZ ; 
 int /*<<< orphan*/  CDNS_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  CDNS_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  CDNS_WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_4096 ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_512 ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_SELECT_4096 ; 
 int /*<<< orphan*/  CDNS_WDT_PRESCALE_SELECT_512 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_wdt_info ; 
 int /*<<< orphan*/  cdns_wdt_irq_handler ; 
 int /*<<< orphan*/  cdns_wdt_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct cdns_wdt* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cdns_wdt*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct cdns_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,scalar_t__) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (struct watchdog_device*) ; 
 int /*<<< orphan*/  wdt_timeout ; 

__attribute__((used)) static int cdns_wdt_probe(struct platform_device *pdev)
{
	struct resource *res;
	int ret, irq;
	unsigned long clock_f;
	struct cdns_wdt *wdt;
	struct watchdog_device *cdns_wdt_device;

	wdt = devm_kzalloc(&pdev->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	cdns_wdt_device = &wdt->cdns_wdt_device;
	cdns_wdt_device->info = &cdns_wdt_info;
	cdns_wdt_device->ops = &cdns_wdt_ops;
	cdns_wdt_device->timeout = CDNS_WDT_DEFAULT_TIMEOUT;
	cdns_wdt_device->min_timeout = CDNS_WDT_MIN_TIMEOUT;
	cdns_wdt_device->max_timeout = CDNS_WDT_MAX_TIMEOUT;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	wdt->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wdt->regs))
		return PTR_ERR(wdt->regs);

	/* Register the interrupt */
	wdt->rst = of_property_read_bool(pdev->dev.of_node, "reset-on-timeout");
	irq = platform_get_irq(pdev, 0);
	if (!wdt->rst && irq >= 0) {
		ret = devm_request_irq(&pdev->dev, irq, cdns_wdt_irq_handler, 0,
				       pdev->name, pdev);
		if (ret) {
			dev_err(&pdev->dev,
				"cannot register interrupt handler err=%d\n",
				ret);
			return ret;
		}
	}

	/* Initialize the members of cdns_wdt structure */
	cdns_wdt_device->parent = &pdev->dev;

	ret = watchdog_init_timeout(cdns_wdt_device, wdt_timeout, &pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "unable to set timeout value\n");
		return ret;
	}

	watchdog_set_nowayout(cdns_wdt_device, nowayout);
	watchdog_stop_on_reboot(cdns_wdt_device);
	watchdog_set_drvdata(cdns_wdt_device, wdt);

	wdt->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(wdt->clk)) {
		dev_err(&pdev->dev, "input clock not found\n");
		ret = PTR_ERR(wdt->clk);
		return ret;
	}

	ret = clk_prepare_enable(wdt->clk);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable clock\n");
		return ret;
	}

	clock_f = clk_get_rate(wdt->clk);
	if (clock_f <= CDNS_WDT_CLK_75MHZ) {
		wdt->prescaler = CDNS_WDT_PRESCALE_512;
		wdt->ctrl_clksel = CDNS_WDT_PRESCALE_SELECT_512;
	} else {
		wdt->prescaler = CDNS_WDT_PRESCALE_4096;
		wdt->ctrl_clksel = CDNS_WDT_PRESCALE_SELECT_4096;
	}

	spin_lock_init(&wdt->io_lock);

	ret = watchdog_register_device(cdns_wdt_device);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register wdt device\n");
		goto err_clk_disable;
	}
	platform_set_drvdata(pdev, wdt);

	dev_info(&pdev->dev, "Xilinx Watchdog Timer at %p with timeout %ds%s\n",
		 wdt->regs, cdns_wdt_device->timeout,
		 nowayout ? ", nowayout" : "");

	return 0;

err_clk_disable:
	clk_disable_unprepare(wdt->clk);

	return ret;
}