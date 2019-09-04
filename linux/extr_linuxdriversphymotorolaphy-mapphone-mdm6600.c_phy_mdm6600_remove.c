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
struct phy_mdm6600 {int /*<<< orphan*/  status_work; int /*<<< orphan*/  bootup_work; int /*<<< orphan*/  modem_wake_work; int /*<<< orphan*/  ack; int /*<<< orphan*/  running; int /*<<< orphan*/  dev; struct gpio_desc** ctrl_gpios; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MDM6600_ENABLED_DELAY_MS ; 
 size_t PHY_MDM6600_RESET ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_mdm6600_device_power_off (struct phy_mdm6600*) ; 
 struct phy_mdm6600* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_mdm6600_remove(struct platform_device *pdev)
{
	struct phy_mdm6600 *ddata = platform_get_drvdata(pdev);
	struct gpio_desc *reset_gpio = ddata->ctrl_gpios[PHY_MDM6600_RESET];

	pm_runtime_dont_use_autosuspend(ddata->dev);
	pm_runtime_put_sync(ddata->dev);
	pm_runtime_disable(ddata->dev);

	if (!ddata->running)
		wait_for_completion_timeout(&ddata->ack,
			msecs_to_jiffies(PHY_MDM6600_ENABLED_DELAY_MS));

	gpiod_set_value_cansleep(reset_gpio, 1);
	phy_mdm6600_device_power_off(ddata);

	cancel_delayed_work_sync(&ddata->modem_wake_work);
	cancel_delayed_work_sync(&ddata->bootup_work);
	cancel_delayed_work_sync(&ddata->status_work);

	return 0;
}