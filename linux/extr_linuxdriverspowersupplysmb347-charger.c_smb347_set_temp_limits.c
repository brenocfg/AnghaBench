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
struct TYPE_2__ {int chip_temp_threshold; int soft_cold_temp_limit; int soft_hot_temp_limit; int hard_cold_temp_limit; int hard_hot_temp_limit; int soft_temp_limit_compensation; scalar_t__ charge_current_compensation; scalar_t__ suspend_on_hard_temp_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_OTG ; 
 int /*<<< orphan*/  CFG_OTG_CC_COMPENSATION_MASK ; 
 int CFG_OTG_CC_COMPENSATION_SHIFT ; 
 int /*<<< orphan*/  CFG_OTG_TEMP_THRESHOLD_MASK ; 
 int CFG_OTG_TEMP_THRESHOLD_SHIFT ; 
 int /*<<< orphan*/  CFG_SYSOK ; 
 int /*<<< orphan*/  CFG_SYSOK_SUSPEND_HARD_LIMIT_DISABLED ; 
 int /*<<< orphan*/  CFG_TEMP_LIMIT ; 
 int /*<<< orphan*/  CFG_TEMP_LIMIT_HARD_COLD_MASK ; 
 int CFG_TEMP_LIMIT_HARD_COLD_SHIFT ; 
 int /*<<< orphan*/  CFG_TEMP_LIMIT_HARD_HOT_MASK ; 
 int CFG_TEMP_LIMIT_HARD_HOT_SHIFT ; 
 int /*<<< orphan*/  CFG_TEMP_LIMIT_SOFT_COLD_MASK ; 
 int CFG_TEMP_LIMIT_SOFT_COLD_SHIFT ; 
 int /*<<< orphan*/  CFG_TEMP_LIMIT_SOFT_HOT_MASK ; 
 int CFG_TEMP_LIMIT_SOFT_HOT_SHIFT ; 
 int /*<<< orphan*/  CFG_THERM ; 
 int /*<<< orphan*/  CFG_THERM_MONITOR_DISABLED ; 
 int /*<<< orphan*/  CFG_THERM_SOFT_COLD_COMPENSATION_MASK ; 
 int CFG_THERM_SOFT_COLD_COMPENSATION_SHIFT ; 
 int /*<<< orphan*/  CFG_THERM_SOFT_HOT_COMPENSATION_MASK ; 
 int CFG_THERM_SOFT_HOT_COMPENSATION_SHIFT ; 
 int SMB347_SOFT_TEMP_COMPENSATE_DEFAULT ; 
 int SMB347_TEMP_USE_DEFAULT ; 
 int /*<<< orphan*/  ccc_tbl ; 
 int clamp_val (int,int,int) ; 
 int current_to_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smb347_set_temp_limits(struct smb347_charger *smb)
{
	bool enable_therm_monitor = false;
	int ret = 0;
	int val;

	if (smb->pdata->chip_temp_threshold) {
		val = smb->pdata->chip_temp_threshold;

		/* degree C */
		val = clamp_val(val, 100, 130) - 100;
		val /= 10;

		ret = regmap_update_bits(smb->regmap, CFG_OTG,
					 CFG_OTG_TEMP_THRESHOLD_MASK,
					 val << CFG_OTG_TEMP_THRESHOLD_SHIFT);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->soft_cold_temp_limit != SMB347_TEMP_USE_DEFAULT) {
		val = smb->pdata->soft_cold_temp_limit;

		val = clamp_val(val, 0, 15);
		val /= 5;
		/* this goes from higher to lower so invert the value */
		val = ~val & 0x3;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_SOFT_COLD_MASK,
					 val << CFG_TEMP_LIMIT_SOFT_COLD_SHIFT);
		if (ret < 0)
			return ret;

		enable_therm_monitor = true;
	}

	if (smb->pdata->soft_hot_temp_limit != SMB347_TEMP_USE_DEFAULT) {
		val = smb->pdata->soft_hot_temp_limit;

		val = clamp_val(val, 40, 55) - 40;
		val /= 5;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_SOFT_HOT_MASK,
					 val << CFG_TEMP_LIMIT_SOFT_HOT_SHIFT);
		if (ret < 0)
			return ret;

		enable_therm_monitor = true;
	}

	if (smb->pdata->hard_cold_temp_limit != SMB347_TEMP_USE_DEFAULT) {
		val = smb->pdata->hard_cold_temp_limit;

		val = clamp_val(val, -5, 10) + 5;
		val /= 5;
		/* this goes from higher to lower so invert the value */
		val = ~val & 0x3;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_HARD_COLD_MASK,
					 val << CFG_TEMP_LIMIT_HARD_COLD_SHIFT);
		if (ret < 0)
			return ret;

		enable_therm_monitor = true;
	}

	if (smb->pdata->hard_hot_temp_limit != SMB347_TEMP_USE_DEFAULT) {
		val = smb->pdata->hard_hot_temp_limit;

		val = clamp_val(val, 50, 65) - 50;
		val /= 5;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_HARD_HOT_MASK,
					 val << CFG_TEMP_LIMIT_HARD_HOT_SHIFT);
		if (ret < 0)
			return ret;

		enable_therm_monitor = true;
	}

	/*
	 * If any of the temperature limits are set, we also enable the
	 * thermistor monitoring.
	 *
	 * When soft limits are hit, the device will start to compensate
	 * current and/or voltage depending on the configuration.
	 *
	 * When hard limit is hit, the device will suspend charging
	 * depending on the configuration.
	 */
	if (enable_therm_monitor) {
		ret = regmap_update_bits(smb->regmap, CFG_THERM,
					 CFG_THERM_MONITOR_DISABLED, 0);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->suspend_on_hard_temp_limit) {
		ret = regmap_update_bits(smb->regmap, CFG_SYSOK,
				 CFG_SYSOK_SUSPEND_HARD_LIMIT_DISABLED, 0);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->soft_temp_limit_compensation !=
	    SMB347_SOFT_TEMP_COMPENSATE_DEFAULT) {
		val = smb->pdata->soft_temp_limit_compensation & 0x3;

		ret = regmap_update_bits(smb->regmap, CFG_THERM,
				 CFG_THERM_SOFT_HOT_COMPENSATION_MASK,
				 val << CFG_THERM_SOFT_HOT_COMPENSATION_SHIFT);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(smb->regmap, CFG_THERM,
				 CFG_THERM_SOFT_COLD_COMPENSATION_MASK,
				 val << CFG_THERM_SOFT_COLD_COMPENSATION_SHIFT);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->charge_current_compensation) {
		val = current_to_hw(ccc_tbl, ARRAY_SIZE(ccc_tbl),
				    smb->pdata->charge_current_compensation);
		if (val < 0)
			return val;

		ret = regmap_update_bits(smb->regmap, CFG_OTG,
				CFG_OTG_CC_COMPENSATION_MASK,
				(val & 0x3) << CFG_OTG_CC_COMPENSATION_SHIFT);
		if (ret < 0)
			return ret;
	}

	return ret;
}