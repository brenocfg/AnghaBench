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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct lp8788_rtc {int /*<<< orphan*/  rdev; int /*<<< orphan*/  alarm; struct lp8788* lp; } ;
struct lp8788 {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  alarm_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ALARM_SEL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct lp8788* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct lp8788_rtc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lp8788_alarm_irq_register (struct platform_device*,struct lp8788_rtc*) ; 
 int /*<<< orphan*/  lp8788_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp8788_rtc*) ; 

__attribute__((used)) static int lp8788_rtc_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct lp8788_rtc *rtc;
	struct device *dev = &pdev->dev;

	rtc = devm_kzalloc(dev, sizeof(struct lp8788_rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->lp = lp;
	rtc->alarm = lp->pdata ? lp->pdata->alarm_sel : DEFAULT_ALARM_SEL;
	platform_set_drvdata(pdev, rtc);

	device_init_wakeup(dev, 1);

	rtc->rdev = devm_rtc_device_register(dev, "lp8788_rtc",
					&lp8788_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rdev)) {
		dev_err(dev, "can not register rtc device\n");
		return PTR_ERR(rtc->rdev);
	}

	if (lp8788_alarm_irq_register(pdev, rtc))
		dev_warn(lp->dev, "no rtc irq handler\n");

	return 0;
}