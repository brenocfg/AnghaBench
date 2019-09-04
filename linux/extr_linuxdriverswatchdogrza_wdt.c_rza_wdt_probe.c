#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max_hw_heartbeat_ms; int min_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct rza_wdt {TYPE_1__ wdev; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int U8_MAX ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct rza_wdt* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rza_wdt_ident ; 
 int /*<<< orphan*/  rza_wdt_ops ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct rza_wdt*) ; 

__attribute__((used)) static int rza_wdt_probe(struct platform_device *pdev)
{
	struct rza_wdt *priv;
	struct resource *res;
	unsigned long rate;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	rate = clk_get_rate(priv->clk);
	if (rate < 16384) {
		dev_err(&pdev->dev, "invalid clock rate (%ld)\n", rate);
		return -ENOENT;
	}

	/* Assume slowest clock rate possible (CKS=7) */
	rate /= 16384;

	priv->wdev.info = &rza_wdt_ident,
	priv->wdev.ops = &rza_wdt_ops,
	priv->wdev.parent = &pdev->dev;

	/*
	 * Since the max possible timeout of our 8-bit count register is less
	 * than a second, we must use max_hw_heartbeat_ms.
	 */
	priv->wdev.max_hw_heartbeat_ms = (1000 * U8_MAX) / rate;
	dev_dbg(&pdev->dev, "max hw timeout of %dms\n",
		 priv->wdev.max_hw_heartbeat_ms);

	priv->wdev.min_timeout = 1;
	priv->wdev.timeout = DEFAULT_TIMEOUT;

	watchdog_init_timeout(&priv->wdev, 0, &pdev->dev);
	watchdog_set_drvdata(&priv->wdev, priv);

	ret = devm_watchdog_register_device(&pdev->dev, &priv->wdev);
	if (ret)
		dev_err(&pdev->dev, "Cannot register watchdog device\n");

	return ret;
}