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
struct platform_device {int dummy; } ;
struct db8500_thermal_zone {int /*<<< orphan*/  therm_work; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct db8500_thermal_zone* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  prcmu_stop_temp_sense () ; 

__attribute__((used)) static int db8500_thermal_suspend(struct platform_device *pdev,
		pm_message_t state)
{
	struct db8500_thermal_zone *pzone = platform_get_drvdata(pdev);

	flush_work(&pzone->therm_work);
	prcmu_stop_temp_sense();

	return 0;
}