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
struct snd_soc_component {int dummy; } ;
struct pm8916_wcd_analog_priv {int micbias_mv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_A_MICB_1_CTL ; 
 int /*<<< orphan*/  CDC_A_MICB_1_VAL ; 
 int MICB_1_CTL_EXT_PRECHARG_EN_ENABLE ; 
 int MICB_1_CTL_EXT_PRECHARG_EN_MASK ; 
 int MICB_1_CTL_INT_PRECHARG_BYP_EXT_PRECHRG_SEL ; 
 int MICB_1_CTL_INT_PRECHARG_BYP_MASK ; 
 int MICB_1_VAL_MICB_OUT_VAL_MASK ; 
 int MICB_VOLTAGE_REGVAL (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct pm8916_wcd_analog_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void pm8916_wcd_analog_micbias_enable(struct snd_soc_component *component)
{
	struct pm8916_wcd_analog_priv *wcd = snd_soc_component_get_drvdata(component);

	snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
			    MICB_1_CTL_EXT_PRECHARG_EN_MASK |
			    MICB_1_CTL_INT_PRECHARG_BYP_MASK,
			    MICB_1_CTL_INT_PRECHARG_BYP_EXT_PRECHRG_SEL
			    | MICB_1_CTL_EXT_PRECHARG_EN_ENABLE);

	if (wcd->micbias_mv) {
		snd_soc_component_update_bits(component, CDC_A_MICB_1_VAL,
				    MICB_1_VAL_MICB_OUT_VAL_MASK,
				    MICB_VOLTAGE_REGVAL(wcd->micbias_mv));
		/*
		 * Special headset needs MICBIAS as 2.7V so wait for
		 * 50 msec for the MICBIAS to reach 2.7 volts.
		 */
		if (wcd->micbias_mv >= 2700)
			msleep(50);
	}

	snd_soc_component_update_bits(component, CDC_A_MICB_1_CTL,
			    MICB_1_CTL_EXT_PRECHARG_EN_MASK |
			    MICB_1_CTL_INT_PRECHARG_BYP_MASK, 0);

}