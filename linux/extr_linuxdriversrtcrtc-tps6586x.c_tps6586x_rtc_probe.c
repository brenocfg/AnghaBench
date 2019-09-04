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
struct tps6586x_rtc {TYPE_1__* rtc; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {unsigned long long range_max; int set_start_time; int /*<<< orphan*/  start_secs; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int CL_SEL_MASK ; 
 int CL_SEL_POS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int OSC_SRC_SEL ; 
 int PRE_BYPASS ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  RTC_CTRL ; 
 int RTC_ENABLE ; 
 int TPS6586X_RTC_CL_SEL_1_5PF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct tps6586x_rtc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tps6586x_rtc*) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mktime64 (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps6586x_rtc*) ; 
 int rtc_register_device (TYPE_1__*) ; 
 struct device* to_tps6586x_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tps6586x_rtc_irq ; 
 int /*<<< orphan*/  tps6586x_rtc_ops ; 
 int tps6586x_update (struct device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tps6586x_rtc_probe(struct platform_device *pdev)
{
	struct device *tps_dev = to_tps6586x_dev(&pdev->dev);
	struct tps6586x_rtc *rtc;
	int ret;

	rtc = devm_kzalloc(&pdev->dev, sizeof(*rtc), GFP_KERNEL);
	if (!rtc)
		return -ENOMEM;

	rtc->dev = &pdev->dev;
	rtc->irq = platform_get_irq(pdev, 0);

	/* 1 kHz tick mode, enable tick counting */
	ret = tps6586x_update(tps_dev, RTC_CTRL,
		RTC_ENABLE | OSC_SRC_SEL |
		((TPS6586X_RTC_CL_SEL_1_5PF << CL_SEL_POS) & CL_SEL_MASK),
		RTC_ENABLE | OSC_SRC_SEL | PRE_BYPASS | CL_SEL_MASK);
	if (ret < 0) {
		dev_err(&pdev->dev, "unable to start counter\n");
		return ret;
	}

	device_init_wakeup(&pdev->dev, 1);

	platform_set_drvdata(pdev, rtc);
	rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtc->rtc)) {
		ret = PTR_ERR(rtc->rtc);
		dev_err(&pdev->dev, "RTC allocate device: ret %d\n", ret);
		goto fail_rtc_register;
	}

	rtc->rtc->ops = &tps6586x_rtc_ops;
	rtc->rtc->range_max = (1ULL << 30) - 1; /* 30-bit seconds */
	rtc->rtc->start_secs = mktime64(2009, 1, 1, 0, 0, 0);
	rtc->rtc->set_start_time = true;

	ret = devm_request_threaded_irq(&pdev->dev, rtc->irq, NULL,
				tps6586x_rtc_irq,
				IRQF_ONESHOT,
				dev_name(&pdev->dev), rtc);
	if (ret < 0) {
		dev_err(&pdev->dev, "request IRQ(%d) failed with ret %d\n",
				rtc->irq, ret);
		goto fail_rtc_register;
	}
	disable_irq(rtc->irq);

	ret = rtc_register_device(rtc->rtc);
	if (ret) {
		dev_err(&pdev->dev, "RTC device register: ret %d\n", ret);
		goto fail_rtc_register;
	}

	return 0;

fail_rtc_register:
	tps6586x_update(tps_dev, RTC_CTRL, 0,
		RTC_ENABLE | OSC_SRC_SEL | PRE_BYPASS | CL_SEL_MASK);
	return ret;
}