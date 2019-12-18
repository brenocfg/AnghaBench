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
struct tas5086_private {int pwm_start_mid_z; scalar_t__ charge_period; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAS5086_OSC_TRIM ; 
 int /*<<< orphan*/  TAS5086_PWM_START ; 
 int TAS5086_PWM_START_MIDZ_FOR_START_1 ; 
 int /*<<< orphan*/  TAS5086_SOFT_MUTE ; 
 int TAS5086_SOFT_MUTE_ALL ; 
 int /*<<< orphan*/  TAS5086_SPLIT_CAP_CHARGE ; 
 int /*<<< orphan*/  TAS5086_SYS_CONTROL_2 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__) ; 
 int index_in_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tas5086_charge_period ; 

__attribute__((used)) static int tas5086_init(struct device *dev, struct tas5086_private *priv)
{
	int ret, i;

	/*
	 * If any of the channels is configured to start in Mid-Z mode,
	 * configure 'part 1' of the PWM starts to use Mid-Z, and tell
	 * all configured mid-z channels to start start under 'part 1'.
	 */
	if (priv->pwm_start_mid_z)
		regmap_write(priv->regmap, TAS5086_PWM_START,
			     TAS5086_PWM_START_MIDZ_FOR_START_1 |
				priv->pwm_start_mid_z);

	/* lookup and set split-capacitor charge period */
	if (priv->charge_period == 0) {
		regmap_write(priv->regmap, TAS5086_SPLIT_CAP_CHARGE, 0);
	} else {
		i = index_in_array(tas5086_charge_period,
				   ARRAY_SIZE(tas5086_charge_period),
				   priv->charge_period);
		if (i >= 0)
			regmap_write(priv->regmap, TAS5086_SPLIT_CAP_CHARGE,
				     i + 0x08);
		else
			dev_warn(dev,
				 "Invalid split-cap charge period of %d ns.\n",
				 priv->charge_period);
	}

	/* enable factory trim */
	ret = regmap_write(priv->regmap, TAS5086_OSC_TRIM, 0x00);
	if (ret < 0)
		return ret;

	/* start all channels */
	ret = regmap_write(priv->regmap, TAS5086_SYS_CONTROL_2, 0x20);
	if (ret < 0)
		return ret;

	/* mute all channels for now */
	ret = regmap_write(priv->regmap, TAS5086_SOFT_MUTE,
			   TAS5086_SOFT_MUTE_ALL);
	if (ret < 0)
		return ret;

	return 0;
}