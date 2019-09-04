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
struct thermal_zone_device {struct spear_thermal_dev* devdata; } ;
struct spear_thermal_dev {unsigned int flags; int /*<<< orphan*/  clk; int /*<<< orphan*/  thermal_base; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct thermal_zone_device* platform_get_drvdata (struct platform_device*) ; 
 unsigned int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear_thermal_exit(struct platform_device *pdev)
{
	unsigned int actual_mask = 0;
	struct thermal_zone_device *spear_thermal = platform_get_drvdata(pdev);
	struct spear_thermal_dev *stdev = spear_thermal->devdata;

	thermal_zone_device_unregister(spear_thermal);

	/* Disable SPEAr Thermal Sensor */
	actual_mask = readl_relaxed(stdev->thermal_base);
	writel_relaxed(actual_mask & ~stdev->flags, stdev->thermal_base);

	clk_disable(stdev->clk);

	return 0;
}