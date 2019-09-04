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
struct smb347_charger {int /*<<< orphan*/  usb; TYPE_1__* pdata; int /*<<< orphan*/  mains; int /*<<< orphan*/  battery; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ use_usb; scalar_t__ use_mains; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQSTAT_C ; 
 unsigned int IRQSTAT_C_TAPER_IRQ ; 
 unsigned int IRQSTAT_C_TERMINATION_IRQ ; 
 unsigned int IRQSTAT_C_TERMINATION_STAT ; 
 int /*<<< orphan*/  IRQSTAT_D ; 
 unsigned int IRQSTAT_D_CHARGE_TIMEOUT_IRQ ; 
 unsigned int IRQSTAT_D_CHARGE_TIMEOUT_STAT ; 
 int /*<<< orphan*/  IRQSTAT_E ; 
 unsigned int IRQSTAT_E_DCIN_UV_IRQ ; 
 unsigned int IRQSTAT_E_USBIN_UV_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  STAT_C ; 
 unsigned int STAT_C_CHARGER_ERROR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  smb347_start_stop_charging (struct smb347_charger*) ; 
 scalar_t__ smb347_update_ps_status (struct smb347_charger*) ; 

__attribute__((used)) static irqreturn_t smb347_interrupt(int irq, void *data)
{
	struct smb347_charger *smb = data;
	unsigned int stat_c, irqstat_c, irqstat_d, irqstat_e;
	bool handled = false;
	int ret;

	ret = regmap_read(smb->regmap, STAT_C, &stat_c);
	if (ret < 0) {
		dev_warn(smb->dev, "reading STAT_C failed\n");
		return IRQ_NONE;
	}

	ret = regmap_read(smb->regmap, IRQSTAT_C, &irqstat_c);
	if (ret < 0) {
		dev_warn(smb->dev, "reading IRQSTAT_C failed\n");
		return IRQ_NONE;
	}

	ret = regmap_read(smb->regmap, IRQSTAT_D, &irqstat_d);
	if (ret < 0) {
		dev_warn(smb->dev, "reading IRQSTAT_D failed\n");
		return IRQ_NONE;
	}

	ret = regmap_read(smb->regmap, IRQSTAT_E, &irqstat_e);
	if (ret < 0) {
		dev_warn(smb->dev, "reading IRQSTAT_E failed\n");
		return IRQ_NONE;
	}

	/*
	 * If we get charger error we report the error back to user.
	 * If the error is recovered charging will resume again.
	 */
	if (stat_c & STAT_C_CHARGER_ERROR) {
		dev_err(smb->dev, "charging stopped due to charger error\n");
		power_supply_changed(smb->battery);
		handled = true;
	}

	/*
	 * If we reached the termination current the battery is charged and
	 * we can update the status now. Charging is automatically
	 * disabled by the hardware.
	 */
	if (irqstat_c & (IRQSTAT_C_TERMINATION_IRQ | IRQSTAT_C_TAPER_IRQ)) {
		if (irqstat_c & IRQSTAT_C_TERMINATION_STAT)
			power_supply_changed(smb->battery);
		dev_dbg(smb->dev, "going to HW maintenance mode\n");
		handled = true;
	}

	/*
	 * If we got a charger timeout INT that means the charge
	 * full is not detected with in charge timeout value.
	 */
	if (irqstat_d & IRQSTAT_D_CHARGE_TIMEOUT_IRQ) {
		dev_dbg(smb->dev, "total Charge Timeout INT received\n");

		if (irqstat_d & IRQSTAT_D_CHARGE_TIMEOUT_STAT)
			dev_warn(smb->dev, "charging stopped due to timeout\n");
		power_supply_changed(smb->battery);
		handled = true;
	}

	/*
	 * If we got an under voltage interrupt it means that AC/USB input
	 * was connected or disconnected.
	 */
	if (irqstat_e & (IRQSTAT_E_USBIN_UV_IRQ | IRQSTAT_E_DCIN_UV_IRQ)) {
		if (smb347_update_ps_status(smb) > 0) {
			smb347_start_stop_charging(smb);
			if (smb->pdata->use_mains)
				power_supply_changed(smb->mains);
			if (smb->pdata->use_usb)
				power_supply_changed(smb->usb);
		}
		handled = true;
	}

	return handled ? IRQ_HANDLED : IRQ_NONE;
}