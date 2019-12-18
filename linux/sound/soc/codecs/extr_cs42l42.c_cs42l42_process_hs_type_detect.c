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
struct cs42l42_private {unsigned int hs_type; int* bias_thresholds; int /*<<< orphan*/  regmap; int /*<<< orphan*/  btn_det_init_dbnce; } ;

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
 int /*<<< orphan*/  CS42L42_DET_INT2_MASK ; 
 int /*<<< orphan*/  CS42L42_DET_INT_STATUS2 ; 
 int CS42L42_EVENT_STAT_SEL_MASK ; 
 int CS42L42_EVENT_STAT_SEL_SHIFT ; 
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
 unsigned int CS42L42_HSDET_TYPE_MASK ; 
 unsigned int CS42L42_HSDET_TYPE_SHIFT ; 
 int CS42L42_HS_DET_LEVEL_MASK ; 
 int CS42L42_HS_DET_LEVEL_SHIFT ; 
 int /*<<< orphan*/  CS42L42_HS_DET_STATUS ; 
 int CS42L42_LATCH_TO_VP_MASK ; 
 int CS42L42_LATCH_TO_VP_SHIFT ; 
 int /*<<< orphan*/  CS42L42_MIC_DET_CTL1 ; 
 int /*<<< orphan*/  CS42L42_MISC_DET_CTL ; 
 int CS42L42_M_DETECT_FT_MASK ; 
 int CS42L42_M_DETECT_FT_SHIFT ; 
 int CS42L42_M_DETECT_TF_MASK ; 
 int CS42L42_M_DETECT_TF_SHIFT ; 
 int CS42L42_M_HSBIAS_HIZ_MASK ; 
 int CS42L42_M_HSBIAS_HIZ_SHIFT ; 
 int CS42L42_M_SHORT_DET_MASK ; 
 int CS42L42_M_SHORT_DET_SHIFT ; 
 int CS42L42_M_SHORT_RLS_MASK ; 
 int CS42L42_M_SHORT_RLS_SHIFT ; 
 int CS42L42_PDN_DONE_MASK ; 
 int CS42L42_PDN_DONE_SHIFT ; 
 int CS42L42_PDN_MIC_LVL_DET_MASK ; 
 int CS42L42_PDN_MIC_LVL_DET_SHIFT ; 
 unsigned int CS42L42_PLUG_CTIA ; 
 unsigned int CS42L42_PLUG_OMTP ; 
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
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cs42l42_process_hs_type_detect(struct cs42l42_private *cs42l42)
{
	unsigned int hs_det_status;
	unsigned int int_status;

	/* Mask the auto detect interrupt */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_CODEC_INT_MASK,
		CS42L42_PDN_DONE_MASK |
		CS42L42_HSDET_AUTO_DONE_MASK,
		(1 << CS42L42_PDN_DONE_SHIFT) |
		(1 << CS42L42_HSDET_AUTO_DONE_SHIFT));

	/* Set hs detect to automatic, disabled mode */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_HSDET_CTL2,
		CS42L42_HSDET_CTRL_MASK |
		CS42L42_HSDET_SET_MASK |
		CS42L42_HSBIAS_REF_MASK |
		CS42L42_HSDET_AUTO_TIME_MASK,
		(2 << CS42L42_HSDET_CTRL_SHIFT) |
		(2 << CS42L42_HSDET_SET_SHIFT) |
		(0 << CS42L42_HSBIAS_REF_SHIFT) |
		(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));

	/* Read and save the hs detection result */
	regmap_read(cs42l42->regmap, CS42L42_HS_DET_STATUS, &hs_det_status);

	cs42l42->hs_type = (hs_det_status & CS42L42_HSDET_TYPE_MASK) >>
				CS42L42_HSDET_TYPE_SHIFT;

	/* Set up button detection */
	if ((cs42l42->hs_type == CS42L42_PLUG_CTIA) ||
	      (cs42l42->hs_type == CS42L42_PLUG_OMTP)) {
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

		/* Set up hs detect level sensitivity */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MIC_DET_CTL1,
			CS42L42_LATCH_TO_VP_MASK |
			CS42L42_EVENT_STAT_SEL_MASK |
			CS42L42_HS_DET_LEVEL_MASK,
			(1 << CS42L42_LATCH_TO_VP_SHIFT) |
			(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
			(cs42l42->bias_thresholds[0] <<
			CS42L42_HS_DET_LEVEL_SHIFT));

		/* Set auto HS bias settings to default */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_HSBIAS_SC_AUTOCTL,
			CS42L42_HSBIAS_SENSE_EN_MASK |
			CS42L42_AUTO_HSBIAS_HIZ_MASK |
			CS42L42_TIP_SENSE_EN_MASK |
			CS42L42_HSBIAS_SENSE_TRIP_MASK,
			(1 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
			(1 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
			(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
			(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

		/* Turn on level detect circuitry */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MISC_DET_CTL,
			CS42L42_DETECT_MODE_MASK |
			CS42L42_HSBIAS_CTL_MASK |
			CS42L42_PDN_MIC_LVL_DET_MASK,
			(0 << CS42L42_DETECT_MODE_SHIFT) |
			(3 << CS42L42_HSBIAS_CTL_SHIFT) |
			(0 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

		msleep(cs42l42->btn_det_init_dbnce);

		/* Clear any button interrupts before unmasking them */
		regmap_read(cs42l42->regmap, CS42L42_DET_INT_STATUS2,
			    &int_status);

		/* Unmask button detect interrupts */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_DET_INT2_MASK,
			CS42L42_M_DETECT_TF_MASK |
			CS42L42_M_DETECT_FT_MASK |
			CS42L42_M_HSBIAS_HIZ_MASK |
			CS42L42_M_SHORT_RLS_MASK |
			CS42L42_M_SHORT_DET_MASK,
			(0 << CS42L42_M_DETECT_TF_SHIFT) |
			(0 << CS42L42_M_DETECT_FT_SHIFT) |
			(0 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
			(1 << CS42L42_M_SHORT_RLS_SHIFT) |
			(1 << CS42L42_M_SHORT_DET_SHIFT));
	} else {
		/* Make sure button detect and HS bias circuits are off */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MISC_DET_CTL,
			CS42L42_DETECT_MODE_MASK |
			CS42L42_HSBIAS_CTL_MASK |
			CS42L42_PDN_MIC_LVL_DET_MASK,
			(0 << CS42L42_DETECT_MODE_SHIFT) |
			(1 << CS42L42_HSBIAS_CTL_SHIFT) |
			(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));
	}

	regmap_update_bits(cs42l42->regmap,
				CS42L42_DAC_CTL2,
				CS42L42_HPOUT_PULLDOWN_MASK |
				CS42L42_HPOUT_LOAD_MASK |
				CS42L42_HPOUT_CLAMP_MASK |
				CS42L42_DAC_HPF_EN_MASK |
				CS42L42_DAC_MON_EN_MASK,
				(0 << CS42L42_HPOUT_PULLDOWN_SHIFT) |
				(0 << CS42L42_HPOUT_LOAD_SHIFT) |
				(0 << CS42L42_HPOUT_CLAMP_SHIFT) |
				(1 << CS42L42_DAC_HPF_EN_SHIFT) |
				(0 << CS42L42_DAC_MON_EN_SHIFT));

	/* Unmask tip sense interrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_TSRS_PLUG_INT_MASK,
		CS42L42_RS_PLUG_MASK |
		CS42L42_RS_UNPLUG_MASK |
		CS42L42_TS_PLUG_MASK |
		CS42L42_TS_UNPLUG_MASK,
		(1 << CS42L42_RS_PLUG_SHIFT) |
		(1 << CS42L42_RS_UNPLUG_SHIFT) |
		(0 << CS42L42_TS_PLUG_SHIFT) |
		(0 << CS42L42_TS_UNPLUG_SHIFT));
}