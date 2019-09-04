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
struct watchdog_device {int min_timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; int /*<<< orphan*/  bootstatus; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ep93xx_wdt_priv {struct watchdog_device wdd; scalar_t__ mmio; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ EP93XX_WATCHDOG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDT_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct ep93xx_wdt_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,struct watchdog_device*) ; 
 int /*<<< orphan*/  ep93xx_wdt_ident ; 
 int /*<<< orphan*/  ep93xx_wdt_ops ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct ep93xx_wdt_priv*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_wdt_probe(struct platform_device *pdev)
{
	struct ep93xx_wdt_priv *priv;
	struct watchdog_device *wdd;
	struct resource *res;
	unsigned long val;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->mmio = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->mmio))
		return PTR_ERR(priv->mmio);

	val = readl(priv->mmio + EP93XX_WATCHDOG);

	wdd = &priv->wdd;
	wdd->bootstatus = (val & 0x01) ? WDIOF_CARDRESET : 0;
	wdd->info = &ep93xx_wdt_ident;
	wdd->ops = &ep93xx_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_hw_heartbeat_ms = 200;
	wdd->parent = &pdev->dev;

	watchdog_set_nowayout(wdd, nowayout);

	wdd->timeout = WDT_TIMEOUT;
	watchdog_init_timeout(wdd, timeout, &pdev->dev);

	watchdog_set_drvdata(wdd, priv);

	ret = devm_watchdog_register_device(&pdev->dev, wdd);
	if (ret)
		return ret;

	dev_info(&pdev->dev, "EP93XX watchdog driver %s\n",
		(val & 0x08) ? " (nCS1 disable detected)" : "");

	return 0;
}