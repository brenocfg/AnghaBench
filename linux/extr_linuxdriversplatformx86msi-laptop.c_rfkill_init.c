#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ ec_delay; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  RFKILL_TYPE_WWAN ; 
 int /*<<< orphan*/  get_wireless_state_ec_standard () ; 
 int /*<<< orphan*/  msi_rfkill_init ; 
 int /*<<< orphan*/  msi_rfkill_work ; 
 TYPE_1__* quirks ; 
 scalar_t__ rfk_bluetooth ; 
 scalar_t__ rfk_threeg ; 
 scalar_t__ rfk_wlan ; 
 scalar_t__ rfkill_alloc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_bluetooth_ops ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int rfkill_register (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_threeg_ops ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_wlan_ops ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ threeg_exists ; 

__attribute__((used)) static int rfkill_init(struct platform_device *sdev)
{
	/* add rfkill */
	int retval;

	/* keep the hardware wireless state */
	get_wireless_state_ec_standard();

	rfk_bluetooth = rfkill_alloc("msi-bluetooth", &sdev->dev,
				RFKILL_TYPE_BLUETOOTH,
				&rfkill_bluetooth_ops, NULL);
	if (!rfk_bluetooth) {
		retval = -ENOMEM;
		goto err_bluetooth;
	}
	retval = rfkill_register(rfk_bluetooth);
	if (retval)
		goto err_bluetooth;

	rfk_wlan = rfkill_alloc("msi-wlan", &sdev->dev, RFKILL_TYPE_WLAN,
				&rfkill_wlan_ops, NULL);
	if (!rfk_wlan) {
		retval = -ENOMEM;
		goto err_wlan;
	}
	retval = rfkill_register(rfk_wlan);
	if (retval)
		goto err_wlan;

	if (threeg_exists) {
		rfk_threeg = rfkill_alloc("msi-threeg", &sdev->dev,
				RFKILL_TYPE_WWAN, &rfkill_threeg_ops, NULL);
		if (!rfk_threeg) {
			retval = -ENOMEM;
			goto err_threeg;
		}
		retval = rfkill_register(rfk_threeg);
		if (retval)
			goto err_threeg;
	}

	/* schedule to run rfkill state initial */
	if (quirks->ec_delay) {
		schedule_delayed_work(&msi_rfkill_init,
			round_jiffies_relative(1 * HZ));
	} else
		schedule_work(&msi_rfkill_work);

	return 0;

err_threeg:
	rfkill_destroy(rfk_threeg);
	if (rfk_wlan)
		rfkill_unregister(rfk_wlan);
err_wlan:
	rfkill_destroy(rfk_wlan);
	if (rfk_bluetooth)
		rfkill_unregister(rfk_bluetooth);
err_bluetooth:
	rfkill_destroy(rfk_bluetooth);

	return retval;
}