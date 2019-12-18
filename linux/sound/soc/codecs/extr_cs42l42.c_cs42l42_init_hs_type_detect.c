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
struct cs42l42_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  hs_bias_ramp_time; } ;

/* Variables and functions */
 int CS42L42_AUTO_HSBIAS_HIZ_MASK ; 
 int CS42L42_AUTO_HSBIAS_HIZ_SHIFT ; 
 int /*<<< orphan*/  CS42L42_CODEC_INT_MASK ; 
 int /*<<< orphan*/  CS42L42_DAC_CTL2 ; 
 int CS42L42_DAC_HPF_EN_MASK ; 
 int CS42L42_DAC_HPF_EN_SHIFT ; 
 int CS42L42_DAC_MON_EN_MASK ; 
 int CS42L42_DAC_MON_EN_SHIFT ; 
 int CS42L42_DETECT_MODE_MASK ; 
 int CS42L42_DETECT_MODE_SHIFT ; 
 int CS42L42_HPOUT_CLAMP_MASK ; 
 int CS42L42_HPOUT_CLAMP_SHIFT ; 
 int CS42L42_HPOUT_LOAD_MASK ; 
 int CS42L42_HPOUT_LOAD_SHIFT ; 
 int CS42L42_HPOUT_PULLDOWN_MASK ; 
 int CS42L42_HPOUT_PULLDOWN_SHIFT ; 
 int CS42L42_HSBIAS_CTL_MASK ; 
 int CS42L42_HSBIAS_CTL_SHIFT ; 
 int CS42L42_HSBIAS_REF_MASK ; 
 int CS42L42_HSBIAS_REF_SHIFT ; 
 int /*<<< orphan*/  CS42L42_HSBIAS_SC_AUTOCTL ; 
 int CS42L42_HSBIAS_SENSE_EN_MASK ; 
 int CS42L42_HSBIAS_SENSE_EN_SHIFT ; 
 int CS42L42_HSBIAS_SENSE_TRIP_MASK ; 
 int CS42L42_HSBIAS_SENSE_TRIP_SHIFT ; 
 int CS42L42_HSDET_AUTO_DONE_MASK ; 
 int CS42L42_HSDET_AUTO_DONE_SHIFT ; 
 int CS42L42_HSDET_AUTO_TIME_MASK ; 
 int CS42L42_HSDET_AUTO_TIME_SHIFT ; 
 int /*<<< orphan*/  CS42L42_HSDET_CTL2 ; 
 int CS42L42_HSDET_CTRL_MASK ; 
 int CS42L42_HSDET_CTRL_SHIFT ; 
 int CS42L42_HSDET_SET_MASK ; 
 int CS42L42_HSDET_SET_SHIFT ; 
 int /*<<< orphan*/  CS42L42_MISC_DET_CTL ; 
 int CS42L42_PDN_DONE_MASK ; 
 int CS42L42_PDN_DONE_SHIFT ; 
 int CS42L42_PDN_MIC_LVL_DET_MASK ; 
 int CS42L42_PDN_MIC_LVL_DET_SHIFT ; 
 int CS42L42_RS_PLUG_MASK ; 
 int CS42L42_RS_PLUG_SHIFT ; 
 int CS42L42_RS_UNPLUG_MASK ; 
 int CS42L42_RS_UNPLUG_SHIFT ; 
 int CS42L42_TIP_SENSE_EN_MASK ; 
 int CS42L42_TIP_SENSE_EN_SHIFT ; 
 int /*<<< orphan*/  CS42L42_TSRS_PLUG_INT_MASK ; 
 int CS42L42_TS_PLUG_MASK ; 
 int CS42L42_TS_PLUG_SHIFT ; 
 int CS42L42_TS_UNPLUG_MASK ; 
 int CS42L42_TS_UNPLUG_SHIFT ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cs42l42_init_hs_type_detect(struct cs42l42_private *cs42l42)
{
	/* Mask tip sense interrupts */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_TSRS_PLUG_INT_MASK,
				CS42L42_RS_PLUG_MASK |
				CS42L42_RS_UNPLUG_MASK |
				CS42L42_TS_PLUG_MASK |
				CS42L42_TS_UNPLUG_MASK,
				(1 << CS42L42_RS_PLUG_SHIFT) |
				(1 << CS42L42_RS_UNPLUG_SHIFT) |
				(1 << CS42L42_TS_PLUG_SHIFT) |
				(1 << CS42L42_TS_UNPLUG_SHIFT));

	/* Make sure button detect and HS bias circuits are off */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_MISC_DET_CTL,
				CS42L42_DETECT_MODE_MASK |
				CS42L42_HSBIAS_CTL_MASK |
				CS42L42_PDN_MIC_LVL_DET_MASK,
				(0 << CS42L42_DETECT_MODE_SHIFT) |
				(1 << CS42L42_HSBIAS_CTL_SHIFT) |
				(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

	/* Set auto HS bias settings to default */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSBIAS_SC_AUTOCTL,
				CS42L42_HSBIAS_SENSE_EN_MASK |
				CS42L42_AUTO_HSBIAS_HIZ_MASK |
				CS42L42_TIP_SENSE_EN_MASK |
				CS42L42_HSBIAS_SENSE_TRIP_MASK,
				(0 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
				(0 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
				(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
				(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

	/* Set hs detect to manual, disabled mode */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSDET_CTL2,
				CS42L42_HSDET_CTRL_MASK |
				CS42L42_HSDET_SET_MASK |
				CS42L42_HSBIAS_REF_MASK |
				CS42L42_HSDET_AUTO_TIME_MASK,
				(0 << CS42L42_HSDET_CTRL_SHIFT) |
				(2 << CS42L42_HSDET_SET_SHIFT) |
				(0 << CS42L42_HSBIAS_REF_SHIFT) |
				(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));

	regmap_update_bits(cs42l42->regmap,
				CS42L42_DAC_CTL2,
				CS42L42_HPOUT_PULLDOWN_MASK |
				CS42L42_HPOUT_LOAD_MASK |
				CS42L42_HPOUT_CLAMP_MASK |
				CS42L42_DAC_HPF_EN_MASK |
				CS42L42_DAC_MON_EN_MASK,
				(8 << CS42L42_HPOUT_PULLDOWN_SHIFT) |
				(0 << CS42L42_HPOUT_LOAD_SHIFT) |
				(1 << CS42L42_HPOUT_CLAMP_SHIFT) |
				(1 << CS42L42_DAC_HPF_EN_SHIFT) |
				(1 << CS42L42_DAC_MON_EN_SHIFT));

	/* Power up HS bias to 2.7V */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_MISC_DET_CTL,
				CS42L42_DETECT_MODE_MASK |
				CS42L42_HSBIAS_CTL_MASK |
				CS42L42_PDN_MIC_LVL_DET_MASK,
				(0 << CS42L42_DETECT_MODE_SHIFT) |
				(3 << CS42L42_HSBIAS_CTL_SHIFT) |
				(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

	/* Wait for HS bias to ramp up */
	msleep(cs42l42->hs_bias_ramp_time);

	/* Unmask auto detect interrupt */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_CODEC_INT_MASK,
				CS42L42_PDN_DONE_MASK |
				CS42L42_HSDET_AUTO_DONE_MASK,
				(1 << CS42L42_PDN_DONE_SHIFT) |
				(0 << CS42L42_HSDET_AUTO_DONE_SHIFT));

	/* Set hs detect to automatic, enabled mode */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSDET_CTL2,
				CS42L42_HSDET_CTRL_MASK |
				CS42L42_HSDET_SET_MASK |
				CS42L42_HSBIAS_REF_MASK |
				CS42L42_HSDET_AUTO_TIME_MASK,
				(3 << CS42L42_HSDET_CTRL_SHIFT) |
				(2 << CS42L42_HSDET_SET_SHIFT) |
				(0 << CS42L42_HSBIAS_REF_SHIFT) |
				(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));
}