#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wm831x_rtc {int alarm_enabled; int /*<<< orphan*/  rtc; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int WM831X_RTC_ALM_ENA ; 
 int /*<<< orphan*/  WM831X_RTC_CONTROL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,...) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 struct wm831x_rtc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wm831x_rtc*) ; 
 int /*<<< orphan*/  devm_rtc_device_register (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm831x_rtc*) ; 
 int /*<<< orphan*/  wm831x_alm_irq ; 
 int wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_rtc_add_randomness (struct wm831x*) ; 
 int /*<<< orphan*/  wm831x_rtc_ops ; 

__attribute__((used)) static int wm831x_rtc_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_rtc *wm831x_rtc;
	int alm_irq = wm831x_irq(wm831x, platform_get_irq_byname(pdev, "ALM"));
	int ret = 0;

	wm831x_rtc = devm_kzalloc(&pdev->dev, sizeof(*wm831x_rtc), GFP_KERNEL);
	if (wm831x_rtc == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, wm831x_rtc);
	wm831x_rtc->wm831x = wm831x;

	ret = wm831x_reg_read(wm831x, WM831X_RTC_CONTROL);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to read RTC control: %d\n", ret);
		goto err;
	}
	if (ret & WM831X_RTC_ALM_ENA)
		wm831x_rtc->alarm_enabled = 1;

	device_init_wakeup(&pdev->dev, 1);

	wm831x_rtc->rtc = devm_rtc_device_register(&pdev->dev, "wm831x",
					      &wm831x_rtc_ops, THIS_MODULE);
	if (IS_ERR(wm831x_rtc->rtc)) {
		ret = PTR_ERR(wm831x_rtc->rtc);
		goto err;
	}

	ret = devm_request_threaded_irq(&pdev->dev, alm_irq, NULL,
				wm831x_alm_irq,
				IRQF_TRIGGER_RISING, "RTC alarm",
				wm831x_rtc);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to request alarm IRQ %d: %d\n",
			alm_irq, ret);
	}

	wm831x_rtc_add_randomness(wm831x);

	return 0;

err:
	return ret;
}