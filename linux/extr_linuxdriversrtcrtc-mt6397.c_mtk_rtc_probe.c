#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mt6397_rtc {scalar_t__ irq; int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  lock; TYPE_1__* dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  addr_base; } ;
struct mt6397_chip {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct mt6397_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct mt6397_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  mtk_rtc_irq_handler_thread ; 
 int /*<<< orphan*/  mtk_rtc_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mt6397_rtc*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct mt6397_rtc*) ; 
 int /*<<< orphan*/  rtc_device_register (char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_rtc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct mt6397_chip *mt6397_chip = dev_get_drvdata(pdev->dev.parent);
	struct mt6397_rtc *rtc;
	int ret;

	rtc = devm_kzalloc(&pdev->dev, sizeof(struct mt6397_rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rtc->addr_base = res->start;

	rtc->irq = platform_get_irq(pdev, 0);
	if (rtc->irq < 0)
		return rtc->irq;

	rtc->regmap = mt6397_chip->regmap;
	rtc->dev = &pdev->dev;
	mutex_init(&rtc->lock);

	platform_set_drvdata(pdev, rtc);

	ret = request_threaded_irq(rtc->irq, NULL,
				   mtk_rtc_irq_handler_thread,
				   IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
				   "mt6397-rtc", rtc);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			rtc->irq, ret);
		goto out_dispose_irq;
	}

	device_init_wakeup(&pdev->dev, 1);

	rtc->rtc_dev = rtc_device_register("mt6397-rtc", &pdev->dev,
					   &mtk_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rtc_dev)) {
		dev_err(&pdev->dev, "register rtc device failed\n");
		ret = PTR_ERR(rtc->rtc_dev);
		goto out_free_irq;
	}

	return 0;

out_free_irq:
	free_irq(rtc->irq, rtc->rtc_dev);
out_dispose_irq:
	irq_dispose_mapping(rtc->irq);
	return ret;
}