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
struct rtc_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rtc_device* devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm355evm_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_device*) ; 

__attribute__((used)) static int dm355evm_rtc_probe(struct platform_device *pdev)
{
	struct rtc_device *rtc;

	rtc = devm_rtc_device_register(&pdev->dev, pdev->name,
					&dm355evm_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc)) {
		dev_err(&pdev->dev, "can't register RTC device, err %ld\n",
			PTR_ERR(rtc));
		return PTR_ERR(rtc);
	}
	platform_set_drvdata(pdev, rtc);

	return 0;
}