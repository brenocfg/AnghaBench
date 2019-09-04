#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct watchdog_device {int timeout; TYPE_1__* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct xwdt_device {int wdt_interval; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * base; int /*<<< orphan*/  spinlock; struct watchdog_device xilinx_wdt_wdd; } ;
struct resource {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int XWT_TIMER_FAILED ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct xwdt_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xwdt_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct xwdt_device*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int) ; 
 int /*<<< orphan*/  xilinx_wdt_ident ; 
 int /*<<< orphan*/  xilinx_wdt_ops ; 
 int xwdt_selftest (struct xwdt_device*) ; 

__attribute__((used)) static int xwdt_probe(struct platform_device *pdev)
{
	int rc;
	u32 pfreq = 0, enable_once = 0;
	struct resource *res;
	struct xwdt_device *xdev;
	struct watchdog_device *xilinx_wdt_wdd;

	xdev = devm_kzalloc(&pdev->dev, sizeof(*xdev), GFP_KERNEL);
	if (!xdev)
		return -ENOMEM;

	xilinx_wdt_wdd = &xdev->xilinx_wdt_wdd;
	xilinx_wdt_wdd->info = &xilinx_wdt_ident;
	xilinx_wdt_wdd->ops = &xilinx_wdt_ops;
	xilinx_wdt_wdd->parent = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xdev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(xdev->base))
		return PTR_ERR(xdev->base);

	rc = of_property_read_u32(pdev->dev.of_node, "xlnx,wdt-interval",
				  &xdev->wdt_interval);
	if (rc)
		dev_warn(&pdev->dev,
			 "Parameter \"xlnx,wdt-interval\" not found\n");

	rc = of_property_read_u32(pdev->dev.of_node, "xlnx,wdt-enable-once",
				  &enable_once);
	if (rc)
		dev_warn(&pdev->dev,
			 "Parameter \"xlnx,wdt-enable-once\" not found\n");

	watchdog_set_nowayout(xilinx_wdt_wdd, enable_once);

	xdev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(xdev->clk)) {
		if (PTR_ERR(xdev->clk) != -ENOENT)
			return PTR_ERR(xdev->clk);

		/*
		 * Clock framework support is optional, continue on
		 * anyways if we don't find a matching clock.
		 */
		xdev->clk = NULL;

		rc = of_property_read_u32(pdev->dev.of_node, "clock-frequency",
					  &pfreq);
		if (rc)
			dev_warn(&pdev->dev,
				 "The watchdog clock freq cannot be obtained\n");
	} else {
		pfreq = clk_get_rate(xdev->clk);
	}

	/*
	 * Twice of the 2^wdt_interval / freq  because the first wdt overflow is
	 * ignored (interrupt), reset is only generated at second wdt overflow
	 */
	if (pfreq && xdev->wdt_interval)
		xilinx_wdt_wdd->timeout = 2 * ((1 << xdev->wdt_interval) /
					  pfreq);

	spin_lock_init(&xdev->spinlock);
	watchdog_set_drvdata(xilinx_wdt_wdd, xdev);

	rc = clk_prepare_enable(xdev->clk);
	if (rc) {
		dev_err(&pdev->dev, "unable to enable clock\n");
		return rc;
	}

	rc = xwdt_selftest(xdev);
	if (rc == XWT_TIMER_FAILED) {
		dev_err(&pdev->dev, "SelfTest routine error\n");
		goto err_clk_disable;
	}

	rc = watchdog_register_device(xilinx_wdt_wdd);
	if (rc) {
		dev_err(&pdev->dev, "Cannot register watchdog (err=%d)\n", rc);
		goto err_clk_disable;
	}

	clk_disable(xdev->clk);

	dev_info(&pdev->dev, "Xilinx Watchdog Timer at %p with timeout %ds\n",
		 xdev->base, xilinx_wdt_wdd->timeout);

	platform_set_drvdata(pdev, xdev);

	return 0;
err_clk_disable:
	clk_disable_unprepare(xdev->clk);

	return rc;
}