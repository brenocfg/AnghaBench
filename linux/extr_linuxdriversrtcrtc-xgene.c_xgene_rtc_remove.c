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
struct xgene_rtc_dev {int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xgene_rtc_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xgene_rtc_alarm_irq_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_rtc_remove(struct platform_device *pdev)
{
	struct xgene_rtc_dev *pdata = platform_get_drvdata(pdev);

	xgene_rtc_alarm_irq_enable(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);
	clk_disable_unprepare(pdata->clk);
	return 0;
}