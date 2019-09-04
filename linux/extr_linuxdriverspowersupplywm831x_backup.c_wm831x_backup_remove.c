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
struct wm831x_backup {int /*<<< orphan*/  backup; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct wm831x_backup* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_backup_remove(struct platform_device *pdev)
{
	struct wm831x_backup *devdata = platform_get_drvdata(pdev);

	power_supply_unregister(devdata->backup);

	return 0;
}