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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pic32_rtc_dev {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pic32_rtc_setaie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pic32_rtc_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pic32_rtc_remove(struct platform_device *pdev)
{
	struct pic32_rtc_dev *pdata = platform_get_drvdata(pdev);

	pic32_rtc_setaie(&pdev->dev, 0);
	clk_unprepare(pdata->clk);
	pdata->clk = NULL;

	return 0;
}