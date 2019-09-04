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
struct smb347_charger {int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {int enable_control; scalar_t__ use_usb_otg; int /*<<< orphan*/  use_usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_OTHER ; 
 unsigned int CFG_OTHER_RID_ENABLED_AUTO_OTG ; 
 unsigned int CFG_OTHER_RID_MASK ; 
 int /*<<< orphan*/  CFG_PIN ; 
 unsigned int CFG_PIN_EN_APSD_IRQ ; 
 unsigned int CFG_PIN_EN_CTRL_ACTIVE_HIGH ; 
 unsigned int CFG_PIN_EN_CTRL_ACTIVE_LOW ; 
 unsigned int CFG_PIN_EN_CTRL_MASK ; 
 int /*<<< orphan*/  CMD_A ; 
 unsigned int CMD_A_SUSPEND_ENABLED ; 
#define  SMB347_CHG_ENABLE_PIN_ACTIVE_HIGH 129 
#define  SMB347_CHG_ENABLE_PIN_ACTIVE_LOW 128 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int smb347_set_charge_current (struct smb347_charger*) ; 
 int smb347_set_current_limits (struct smb347_charger*) ; 
 int smb347_set_temp_limits (struct smb347_charger*) ; 
 int smb347_set_voltage_limits (struct smb347_charger*) ; 
 int smb347_set_writable (struct smb347_charger*,int) ; 
 int smb347_start_stop_charging (struct smb347_charger*) ; 
 int smb347_update_ps_status (struct smb347_charger*) ; 

__attribute__((used)) static int smb347_hw_init(struct smb347_charger *smb)
{
	unsigned int val;
	int ret;

	ret = smb347_set_writable(smb, true);
	if (ret < 0)
		return ret;

	/*
	 * Program the platform specific configuration values to the device
	 * first.
	 */
	ret = smb347_set_charge_current(smb);
	if (ret < 0)
		goto fail;

	ret = smb347_set_current_limits(smb);
	if (ret < 0)
		goto fail;

	ret = smb347_set_voltage_limits(smb);
	if (ret < 0)
		goto fail;

	ret = smb347_set_temp_limits(smb);
	if (ret < 0)
		goto fail;

	/* If USB charging is disabled we put the USB in suspend mode */
	if (!smb->pdata->use_usb) {
		ret = regmap_update_bits(smb->regmap, CMD_A,
					 CMD_A_SUSPEND_ENABLED,
					 CMD_A_SUSPEND_ENABLED);
		if (ret < 0)
			goto fail;
	}

	/*
	 * If configured by platform data, we enable hardware Auto-OTG
	 * support for driving VBUS. Otherwise we disable it.
	 */
	ret = regmap_update_bits(smb->regmap, CFG_OTHER, CFG_OTHER_RID_MASK,
		smb->pdata->use_usb_otg ? CFG_OTHER_RID_ENABLED_AUTO_OTG : 0);
	if (ret < 0)
		goto fail;

	/*
	 * Make the charging functionality controllable by a write to the
	 * command register unless pin control is specified in the platform
	 * data.
	 */
	switch (smb->pdata->enable_control) {
	case SMB347_CHG_ENABLE_PIN_ACTIVE_LOW:
		val = CFG_PIN_EN_CTRL_ACTIVE_LOW;
		break;
	case SMB347_CHG_ENABLE_PIN_ACTIVE_HIGH:
		val = CFG_PIN_EN_CTRL_ACTIVE_HIGH;
		break;
	default:
		val = 0;
		break;
	}

	ret = regmap_update_bits(smb->regmap, CFG_PIN, CFG_PIN_EN_CTRL_MASK,
				 val);
	if (ret < 0)
		goto fail;

	/* Disable Automatic Power Source Detection (APSD) interrupt. */
	ret = regmap_update_bits(smb->regmap, CFG_PIN, CFG_PIN_EN_APSD_IRQ, 0);
	if (ret < 0)
		goto fail;

	ret = smb347_update_ps_status(smb);
	if (ret < 0)
		goto fail;

	ret = smb347_start_stop_charging(smb);

fail:
	smb347_set_writable(smb, false);
	return ret;
}