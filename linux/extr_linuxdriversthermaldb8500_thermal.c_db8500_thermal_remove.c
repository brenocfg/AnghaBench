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
struct db8500_thermal_zone {int /*<<< orphan*/  th_lock; int /*<<< orphan*/  therm_work; int /*<<< orphan*/  therm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct db8500_thermal_zone* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db8500_thermal_remove(struct platform_device *pdev)
{
	struct db8500_thermal_zone *pzone = platform_get_drvdata(pdev);

	thermal_zone_device_unregister(pzone->therm_dev);
	cancel_work_sync(&pzone->therm_work);
	mutex_destroy(&pzone->th_lock);

	return 0;
}