#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; TYPE_1__* id_entry; } ;
struct max8998_rtc_info {int lp3974_bug_workaround; int /*<<< orphan*/  irq; int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  rtc; struct max8998_dev* max8998; TYPE_2__* dev; } ;
struct max8998_platform_data {scalar_t__ rtc_delay; } ;
struct max8998_dev {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  rtc; struct max8998_platform_data* pdata; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX8998_IRQ_ALARM0 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,...) ; 
 struct max8998_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct max8998_rtc_info* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct max8998_rtc_info*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8998_rtc_alarm_irq ; 
 int /*<<< orphan*/  max8998_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8998_rtc_info*) ; 

__attribute__((used)) static int max8998_rtc_probe(struct platform_device *pdev)
{
	struct max8998_dev *max8998 = dev_get_drvdata(pdev->dev.parent);
	struct max8998_platform_data *pdata = max8998->pdata;
	struct max8998_rtc_info *info;
	int ret;

	info = devm_kzalloc(&pdev->dev, sizeof(struct max8998_rtc_info),
			GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;
	info->max8998 = max8998;
	info->rtc = max8998->rtc;

	platform_set_drvdata(pdev, info);

	info->rtc_dev = devm_rtc_device_register(&pdev->dev, "max8998-rtc",
			&max8998_rtc_ops, THIS_MODULE);

	if (IS_ERR(info->rtc_dev)) {
		ret = PTR_ERR(info->rtc_dev);
		dev_err(&pdev->dev, "Failed to register RTC device: %d\n", ret);
		return ret;
	}

	if (!max8998->irq_domain)
		goto no_irq;

	info->irq = irq_create_mapping(max8998->irq_domain, MAX8998_IRQ_ALARM0);
	if (!info->irq) {
		dev_warn(&pdev->dev, "Failed to map alarm IRQ\n");
		goto no_irq;
	}

	ret = devm_request_threaded_irq(&pdev->dev, info->irq, NULL,
				max8998_rtc_alarm_irq, 0, "rtc-alarm0", info);

	if (ret < 0)
		dev_err(&pdev->dev, "Failed to request alarm IRQ: %d: %d\n",
			info->irq, ret);

no_irq:
	dev_info(&pdev->dev, "RTC CHIP NAME: %s\n", pdev->id_entry->name);
	if (pdata && pdata->rtc_delay) {
		info->lp3974_bug_workaround = true;
		dev_warn(&pdev->dev, "LP3974 with RTC REGERR option."
				" RTC updates will be extremely slow.\n");
	}

	return 0;
}