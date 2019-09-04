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
typedef  int u8 ;
struct rtc_device {int uie_unsupported; } ;
struct rtc_class_ops {int dummy; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int /*<<< orphan*/  AB8500_RTC_STAT_REG ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int RTC_STATUS_DATA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int ab8500_sysfs_rtc_register (int /*<<< orphan*/ *) ; 
 int abx500_get_register_interruptible (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_pm_set_wake_irq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rtc_device*) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,char*,struct rtc_class_ops*,int /*<<< orphan*/ ) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_alarm_handler ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ab8500_rtc_probe(struct platform_device *pdev)
{
	const struct platform_device_id *platid = platform_get_device_id(pdev);
	int err;
	struct rtc_device *rtc;
	u8 rtc_ctrl;
	int irq;

	irq = platform_get_irq_byname(pdev, "ALARM");
	if (irq < 0)
		return irq;

	/* For RTC supply test */
	err = abx500_mask_and_set_register_interruptible(&pdev->dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, RTC_STATUS_DATA, RTC_STATUS_DATA);
	if (err < 0)
		return err;

	/* Wait for reset by the PorRtc */
	usleep_range(1000, 5000);

	err = abx500_get_register_interruptible(&pdev->dev, AB8500_RTC,
		AB8500_RTC_STAT_REG, &rtc_ctrl);
	if (err < 0)
		return err;

	/* Check if the RTC Supply fails */
	if (!(rtc_ctrl & RTC_STATUS_DATA)) {
		dev_err(&pdev->dev, "RTC supply failure\n");
		return -ENODEV;
	}

	device_init_wakeup(&pdev->dev, true);

	rtc = devm_rtc_device_register(&pdev->dev, "ab8500-rtc",
				(struct rtc_class_ops *)platid->driver_data,
				THIS_MODULE);
	if (IS_ERR(rtc)) {
		dev_err(&pdev->dev, "Registration failed\n");
		err = PTR_ERR(rtc);
		return err;
	}

	err = devm_request_threaded_irq(&pdev->dev, irq, NULL,
			rtc_alarm_handler, IRQF_ONESHOT,
			"ab8500-rtc", rtc);
	if (err < 0)
		return err;

	dev_pm_set_wake_irq(&pdev->dev, irq);
	platform_set_drvdata(pdev, rtc);

	err = ab8500_sysfs_rtc_register(&pdev->dev);
	if (err) {
		dev_err(&pdev->dev, "sysfs RTC failed to register\n");
		return err;
	}

	rtc->uie_unsupported = 1;

	return 0;
}