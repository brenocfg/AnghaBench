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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {void* timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/  min_timeout; void* max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct mtk_wdt_dev {TYPE_1__ wdt_dev; int /*<<< orphan*/  wdt_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct mtk_wdt_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_wdt_info ; 
 int /*<<< orphan*/  mtk_wdt_ops ; 
 int /*<<< orphan*/  mtk_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_wdt_dev*) ; 
 int /*<<< orphan*/  timeout ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct mtk_wdt_dev*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 

__attribute__((used)) static int mtk_wdt_probe(struct platform_device *pdev)
{
	struct mtk_wdt_dev *mtk_wdt;
	struct resource *res;
	int err;

	mtk_wdt = devm_kzalloc(&pdev->dev, sizeof(*mtk_wdt), GFP_KERNEL);
	if (!mtk_wdt)
		return -ENOMEM;

	platform_set_drvdata(pdev, mtk_wdt);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mtk_wdt->wdt_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mtk_wdt->wdt_base))
		return PTR_ERR(mtk_wdt->wdt_base);

	mtk_wdt->wdt_dev.info = &mtk_wdt_info;
	mtk_wdt->wdt_dev.ops = &mtk_wdt_ops;
	mtk_wdt->wdt_dev.timeout = WDT_MAX_TIMEOUT;
	mtk_wdt->wdt_dev.max_timeout = WDT_MAX_TIMEOUT;
	mtk_wdt->wdt_dev.min_timeout = WDT_MIN_TIMEOUT;
	mtk_wdt->wdt_dev.parent = &pdev->dev;

	watchdog_init_timeout(&mtk_wdt->wdt_dev, timeout, &pdev->dev);
	watchdog_set_nowayout(&mtk_wdt->wdt_dev, nowayout);
	watchdog_set_restart_priority(&mtk_wdt->wdt_dev, 128);

	watchdog_set_drvdata(&mtk_wdt->wdt_dev, mtk_wdt);

	mtk_wdt_stop(&mtk_wdt->wdt_dev);

	err = watchdog_register_device(&mtk_wdt->wdt_dev);
	if (unlikely(err))
		return err;

	dev_info(&pdev->dev, "Watchdog enabled (timeout=%d sec, nowayout=%d)\n",
			mtk_wdt->wdt_dev.timeout, nowayout);

	return 0;
}