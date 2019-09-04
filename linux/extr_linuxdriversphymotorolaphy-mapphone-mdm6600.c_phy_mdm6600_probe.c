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
struct phy_mdm6600 {int /*<<< orphan*/ * dev; int /*<<< orphan*/  bootup_work; int /*<<< orphan*/  phy_provider; int /*<<< orphan*/  generic_phy; int /*<<< orphan*/  ack; int /*<<< orphan*/  modem_wake_work; int /*<<< orphan*/  status_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDM6600_MODEM_IDLE_DELAY_MS ; 
 scalar_t__ PHY_MDM6600_PHY_DELAY_MS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct phy_mdm6600* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_phy_provider_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_usb_ops ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_mdm6600_deferred_power_on ; 
 int /*<<< orphan*/  phy_mdm6600_device_power_off (struct phy_mdm6600*) ; 
 int /*<<< orphan*/  phy_mdm6600_init_irq (struct phy_mdm6600*) ; 
 int phy_mdm6600_init_lines (struct phy_mdm6600*) ; 
 int /*<<< orphan*/  phy_mdm6600_modem_wake ; 
 int /*<<< orphan*/  phy_mdm6600_status ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct phy_mdm6600*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct phy_mdm6600*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_mdm6600_probe(struct platform_device *pdev)
{
	struct phy_mdm6600 *ddata;
	int error;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	INIT_DELAYED_WORK(&ddata->bootup_work,
			  phy_mdm6600_deferred_power_on);
	INIT_DELAYED_WORK(&ddata->status_work, phy_mdm6600_status);
	INIT_DELAYED_WORK(&ddata->modem_wake_work, phy_mdm6600_modem_wake);
	init_completion(&ddata->ack);

	ddata->dev = &pdev->dev;
	platform_set_drvdata(pdev, ddata);

	error = phy_mdm6600_init_lines(ddata);
	if (error)
		return error;

	phy_mdm6600_init_irq(ddata);

	ddata->generic_phy = devm_phy_create(ddata->dev, NULL, &gpio_usb_ops);
	if (IS_ERR(ddata->generic_phy)) {
		error = PTR_ERR(ddata->generic_phy);
		goto cleanup;
	}

	phy_set_drvdata(ddata->generic_phy, ddata);

	ddata->phy_provider =
		devm_of_phy_provider_register(ddata->dev,
					      of_phy_simple_xlate);
	if (IS_ERR(ddata->phy_provider)) {
		error = PTR_ERR(ddata->phy_provider);
		goto cleanup;
	}

	schedule_delayed_work(&ddata->bootup_work, 0);

	/*
	 * See phy_mdm6600_device_power_on(). We should be able
	 * to remove this eventually when ohci-platform can deal
	 * with -EPROBE_DEFER.
	 */
	msleep(PHY_MDM6600_PHY_DELAY_MS + 500);

	/*
	 * Enable PM runtime only after PHY has been powered up properly.
	 * It is currently only needed after USB suspends mdm6600 and n_gsm
	 * needs to access the device. We don't want to do this earlier as
	 * gpio mode0 pin doubles as mdm6600 wake-up gpio.
	 */
	pm_runtime_use_autosuspend(ddata->dev);
	pm_runtime_set_autosuspend_delay(ddata->dev,
					 MDM6600_MODEM_IDLE_DELAY_MS);
	pm_runtime_enable(ddata->dev);
	error = pm_runtime_get_sync(ddata->dev);
	if (error < 0) {
		dev_warn(ddata->dev, "failed to wake modem: %i\n", error);
		pm_runtime_put_noidle(ddata->dev);
	}
	pm_runtime_mark_last_busy(ddata->dev);
	pm_runtime_put_autosuspend(ddata->dev);

	return 0;

cleanup:
	phy_mdm6600_device_power_off(ddata);
	return error;
}