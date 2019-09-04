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
typedef  int uint8_t ;
struct max8973_regulator_platform_data {int control_flags; scalar_t__ junction_temp_warning; } ;
struct TYPE_2__ {int ramp_delay; int enable_time; } ;
struct max8973_chip {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; scalar_t__ enable_external_control; TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ MAX77621 ; 
 scalar_t__ MAX77621_TJINT_WARNING_TEMP_120 ; 
 int MAX77621_T_JUNCTION_120 ; 
 scalar_t__ MAX8973 ; 
 int MAX8973_AD_ENABLE ; 
 int MAX8973_BIAS_ENABLE ; 
 int MAX8973_CKKADV_TRIP_150mV_PER_US ; 
 int MAX8973_CKKADV_TRIP_75mV_PER_US ; 
 int MAX8973_CKKADV_TRIP_75mV_PER_US_HIST_DIS ; 
 int MAX8973_CKKADV_TRIP_DISABLE ; 
 int /*<<< orphan*/  MAX8973_CONTROL1 ; 
 int /*<<< orphan*/  MAX8973_CONTROL2 ; 
 int MAX8973_CONTROL_BIAS_ENABLE ; 
#define  MAX8973_CONTROL_CLKADV_TRIP_150mV_PER_US 139 
#define  MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US 138 
#define  MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US_HIST_DIS 137 
#define  MAX8973_CONTROL_CLKADV_TRIP_DISABLED 136 
 int MAX8973_CONTROL_CLKADV_TRIP_MASK ; 
 int MAX8973_CONTROL_FALLING_SLEW_RATE_ENABLE ; 
 int MAX8973_CONTROL_FREQ_SHIFT_9PER_ENABLE ; 
 int MAX8973_CONTROL_INDUCTOR_VALUE_MASK ; 
#define  MAX8973_CONTROL_INDUCTOR_VALUE_MINUS_30_PER 135 
#define  MAX8973_CONTROL_INDUCTOR_VALUE_NOMINAL 134 
#define  MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_30_PER 133 
#define  MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_60_PER 132 
 int MAX8973_CONTROL_OUTPUT_ACTIVE_DISCH_ENABLE ; 
 int MAX8973_CONTROL_PULL_DOWN_ENABLE ; 
 int MAX8973_CONTROL_REMOTE_SENSE_ENABLE ; 
 int MAX8973_DISCH_ENBABLE ; 
 int MAX8973_FREQSHIFT_9PER ; 
 int MAX8973_INDUCTOR_MIN_30_PER ; 
 int MAX8973_INDUCTOR_NOMINAL ; 
 int MAX8973_INDUCTOR_PLUS_30_PER ; 
 int MAX8973_INDUCTOR_PLUS_60_PER ; 
 int MAX8973_NFSR_ENABLE ; 
#define  MAX8973_RAMP_12mV_PER_US 131 
#define  MAX8973_RAMP_200mV_PER_US 130 
#define  MAX8973_RAMP_25mV_PER_US 129 
#define  MAX8973_RAMP_50mV_PER_US 128 
 unsigned int MAX8973_RAMP_MASK ; 
 int MAX8973_SNS_ENABLE ; 
 int /*<<< orphan*/  MAX8973_VOUT ; 
 int /*<<< orphan*/  MAX8973_VOUT_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max8973_init_dcdc(struct max8973_chip *max,
			     struct max8973_regulator_platform_data *pdata)
{
	int ret;
	uint8_t	control1 = 0;
	uint8_t control2 = 0;
	unsigned int data;

	ret = regmap_read(max->regmap, MAX8973_CONTROL1, &data);
	if (ret < 0) {
		dev_err(max->dev, "register %d read failed, err = %d",
				MAX8973_CONTROL1, ret);
		return ret;
	}
	control1 = data & MAX8973_RAMP_MASK;
	switch (control1) {
	case MAX8973_RAMP_12mV_PER_US:
		max->desc.ramp_delay = 12000;
		break;
	case MAX8973_RAMP_25mV_PER_US:
		max->desc.ramp_delay = 25000;
		break;
	case MAX8973_RAMP_50mV_PER_US:
		max->desc.ramp_delay = 50000;
		break;
	case MAX8973_RAMP_200mV_PER_US:
		max->desc.ramp_delay = 200000;
		break;
	}

	if (pdata->control_flags & MAX8973_CONTROL_REMOTE_SENSE_ENABLE)
		control1 |= MAX8973_SNS_ENABLE;

	if (!(pdata->control_flags & MAX8973_CONTROL_FALLING_SLEW_RATE_ENABLE))
		control1 |= MAX8973_NFSR_ENABLE;

	if (pdata->control_flags & MAX8973_CONTROL_OUTPUT_ACTIVE_DISCH_ENABLE)
		control1 |= MAX8973_AD_ENABLE;

	if (pdata->control_flags & MAX8973_CONTROL_BIAS_ENABLE) {
		control1 |= MAX8973_BIAS_ENABLE;
		max->desc.enable_time = 20;
	} else {
		max->desc.enable_time = 240;
	}

	if (pdata->control_flags & MAX8973_CONTROL_FREQ_SHIFT_9PER_ENABLE)
		control1 |= MAX8973_FREQSHIFT_9PER;

	if ((pdata->junction_temp_warning == MAX77621_TJINT_WARNING_TEMP_120) &&
	    (max->id == MAX77621))
		control2 |= MAX77621_T_JUNCTION_120;

	if (!(pdata->control_flags & MAX8973_CONTROL_PULL_DOWN_ENABLE))
		control2 |= MAX8973_DISCH_ENBABLE;

	/*  Clock advance trip configuration */
	switch (pdata->control_flags & MAX8973_CONTROL_CLKADV_TRIP_MASK) {
	case MAX8973_CONTROL_CLKADV_TRIP_DISABLED:
		control2 |= MAX8973_CKKADV_TRIP_DISABLE;
		break;

	case MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US:
		control2 |= MAX8973_CKKADV_TRIP_75mV_PER_US;
		break;

	case MAX8973_CONTROL_CLKADV_TRIP_150mV_PER_US:
		control2 |= MAX8973_CKKADV_TRIP_150mV_PER_US;
		break;

	case MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US_HIST_DIS:
		control2 |= MAX8973_CKKADV_TRIP_75mV_PER_US_HIST_DIS;
		break;
	}

	/* Configure inductor value */
	switch (pdata->control_flags & MAX8973_CONTROL_INDUCTOR_VALUE_MASK) {
	case MAX8973_CONTROL_INDUCTOR_VALUE_NOMINAL:
		control2 |= MAX8973_INDUCTOR_NOMINAL;
		break;

	case MAX8973_CONTROL_INDUCTOR_VALUE_MINUS_30_PER:
		control2 |= MAX8973_INDUCTOR_MIN_30_PER;
		break;

	case MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_30_PER:
		control2 |= MAX8973_INDUCTOR_PLUS_30_PER;
		break;

	case MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_60_PER:
		control2 |= MAX8973_INDUCTOR_PLUS_60_PER;
		break;
	}

	ret = regmap_write(max->regmap, MAX8973_CONTROL1, control1);
	if (ret < 0) {
		dev_err(max->dev, "register %d write failed, err = %d",
				MAX8973_CONTROL1, ret);
		return ret;
	}

	ret = regmap_write(max->regmap, MAX8973_CONTROL2, control2);
	if (ret < 0) {
		dev_err(max->dev, "register %d write failed, err = %d",
				MAX8973_CONTROL2, ret);
		return ret;
	}

	/* If external control is enabled then disable EN bit */
	if (max->enable_external_control && (max->id == MAX8973)) {
		ret = regmap_update_bits(max->regmap, MAX8973_VOUT,
						MAX8973_VOUT_ENABLE, 0);
		if (ret < 0)
			dev_err(max->dev, "register %d update failed, err = %d",
				MAX8973_VOUT, ret);
	}
	return ret;
}