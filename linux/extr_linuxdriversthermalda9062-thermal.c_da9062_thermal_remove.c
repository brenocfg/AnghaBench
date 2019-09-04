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
struct da9062_thermal {int /*<<< orphan*/  zone; int /*<<< orphan*/  work; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct da9062_thermal*) ; 
 struct da9062_thermal* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9062_thermal_remove(struct platform_device *pdev)
{
	struct	da9062_thermal *thermal = platform_get_drvdata(pdev);

	free_irq(thermal->irq, thermal);
	cancel_delayed_work_sync(&thermal->work);
	thermal_zone_device_unregister(thermal->zone);
	return 0;
}