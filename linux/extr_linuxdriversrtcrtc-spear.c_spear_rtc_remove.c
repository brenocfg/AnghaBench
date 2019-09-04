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
struct spear_rtc_config {int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spear_rtc_config* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spear_rtc_disable_interrupt (struct spear_rtc_config*) ; 

__attribute__((used)) static int spear_rtc_remove(struct platform_device *pdev)
{
	struct spear_rtc_config *config = platform_get_drvdata(pdev);

	spear_rtc_disable_interrupt(config);
	clk_disable_unprepare(config->clk);
	device_init_wakeup(&pdev->dev, 0);

	return 0;
}