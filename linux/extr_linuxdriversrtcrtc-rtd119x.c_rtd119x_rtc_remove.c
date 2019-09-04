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
struct rtd119x_rtc {int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct rtd119x_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtd119x_rtc_set_enabled (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtd119x_rtc_remove(struct platform_device *pdev)
{
	struct rtd119x_rtc *data = platform_get_drvdata(pdev);

	rtd119x_rtc_set_enabled(&pdev->dev, false);

	clk_disable_unprepare(data->clk);
	clk_put(data->clk);

	return 0;
}