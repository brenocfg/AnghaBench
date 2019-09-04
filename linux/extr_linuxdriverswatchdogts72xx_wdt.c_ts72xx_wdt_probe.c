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
struct watchdog_device {int min_timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct ts72xx_wdt_priv {struct watchdog_device wdd; void* feed_reg; void* control_reg; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  TS72XX_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct ts72xx_wdt_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,struct watchdog_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  ts72xx_wdt_ident ; 
 int /*<<< orphan*/  ts72xx_wdt_ops ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct ts72xx_wdt_priv*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts72xx_wdt_probe(struct platform_device *pdev)
{
	struct ts72xx_wdt_priv *priv;
	struct watchdog_device *wdd;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->control_reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->control_reg))
		return PTR_ERR(priv->control_reg);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->feed_reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->feed_reg))
		return PTR_ERR(priv->feed_reg);

	wdd = &priv->wdd;
	wdd->info = &ts72xx_wdt_ident;
	wdd->ops = &ts72xx_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_hw_heartbeat_ms = 8000;
	wdd->parent = &pdev->dev;

	watchdog_set_nowayout(wdd, nowayout);

	wdd->timeout = TS72XX_WDT_DEFAULT_TIMEOUT;
	watchdog_init_timeout(wdd, timeout, &pdev->dev);

	watchdog_set_drvdata(wdd, priv);

	ret = devm_watchdog_register_device(&pdev->dev, wdd);
	if (ret)
		return ret;

	dev_info(&pdev->dev, "TS-72xx Watchdog driver\n");

	return 0;
}