#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcf50633_rtc {int /*<<< orphan*/  pcf; int /*<<< orphan*/  rtc_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCF50633_IRQ_ALARM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_to_pcf50633 (int /*<<< orphan*/ ) ; 
 struct pcf50633_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf50633_register_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcf50633_rtc*) ; 
 int /*<<< orphan*/  pcf50633_rtc_irq ; 
 int /*<<< orphan*/  pcf50633_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pcf50633_rtc*) ; 

__attribute__((used)) static int pcf50633_rtc_probe(struct platform_device *pdev)
{
	struct pcf50633_rtc *rtc;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->pcf = dev_to_pcf50633(pdev->dev.parent);
	platform_set_drvdata(pdev, rtc);
	rtc->rtc_dev = devm_rtc_device_register(&pdev->dev, "pcf50633-rtc",
				&pcf50633_rtc_ops, THIS_MODULE);

	if (IS_ERR(rtc->rtc_dev))
		return PTR_ERR(rtc->rtc_dev);

	pcf50633_register_irq(rtc->pcf, PCF50633_IRQ_ALARM,
					pcf50633_rtc_irq, rtc);
	return 0;
}