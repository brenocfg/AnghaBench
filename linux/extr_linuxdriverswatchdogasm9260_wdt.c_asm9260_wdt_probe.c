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
struct watchdog_device {int min_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct asm9260_wdt_priv {size_t mode; scalar_t__ irq; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk; int /*<<< orphan*/  wdt_freq; struct watchdog_device wdd; int /*<<< orphan*/  rst; int /*<<< orphan*/  iobase; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASM9260_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  BM_WDTC_MAX (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HW_RESET ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int asm9260_wdt_get_dt_clks (struct asm9260_wdt_priv*) ; 
 int /*<<< orphan*/  asm9260_wdt_get_dt_mode (struct asm9260_wdt_priv*) ; 
 int /*<<< orphan*/  asm9260_wdt_ident ; 
 int /*<<< orphan*/  asm9260_wdt_irq ; 
 int /*<<< orphan*/  asm9260_wdt_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct asm9260_wdt_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct asm9260_wdt_priv*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct asm9260_wdt_priv*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct asm9260_wdt_priv*) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (struct watchdog_device*,int) ; 

__attribute__((used)) static int asm9260_wdt_probe(struct platform_device *pdev)
{
	struct asm9260_wdt_priv *priv;
	struct watchdog_device *wdd;
	struct resource *res;
	int ret;
	const char * const mode_name[] = { "hw", "sw", "debug", };

	priv = devm_kzalloc(&pdev->dev, sizeof(struct asm9260_wdt_priv),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->iobase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->iobase))
		return PTR_ERR(priv->iobase);

	priv->rst = devm_reset_control_get_exclusive(&pdev->dev, "wdt_rst");
	if (IS_ERR(priv->rst))
		return PTR_ERR(priv->rst);

	ret = asm9260_wdt_get_dt_clks(priv);
	if (ret)
		return ret;

	wdd = &priv->wdd;
	wdd->info = &asm9260_wdt_ident;
	wdd->ops = &asm9260_wdt_ops;
	wdd->min_timeout = 1;
	wdd->max_timeout = BM_WDTC_MAX(priv->wdt_freq);
	wdd->parent = &pdev->dev;

	watchdog_set_drvdata(wdd, priv);

	/*
	 * If 'timeout-sec' unspecified in devicetree, assume a 30 second
	 * default, unless the max timeout is less than 30 seconds, then use
	 * the max instead.
	 */
	wdd->timeout = ASM9260_WDT_DEFAULT_TIMEOUT;
	watchdog_init_timeout(wdd, 0, &pdev->dev);

	asm9260_wdt_get_dt_mode(priv);

	if (priv->mode != HW_RESET)
		priv->irq = platform_get_irq(pdev, 0);

	if (priv->irq > 0) {
		/*
		 * Not all supported platforms specify an interrupt for the
		 * watchdog, so let's make it optional.
		 */
		ret = devm_request_irq(&pdev->dev, priv->irq,
				       asm9260_wdt_irq, 0, pdev->name, priv);
		if (ret < 0)
			dev_warn(&pdev->dev, "failed to request IRQ\n");
	}

	watchdog_set_restart_priority(wdd, 128);

	ret = watchdog_register_device(wdd);
	if (ret)
		goto clk_off;

	platform_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Watchdog enabled (timeout: %d sec, mode: %s)\n",
		 wdd->timeout, mode_name[priv->mode]);
	return 0;

clk_off:
	clk_disable_unprepare(priv->clk);
	clk_disable_unprepare(priv->clk_ahb);
	return ret;
}