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
struct cs42l42_private {int* bias_thresholds; char plug_state; int /*<<< orphan*/  regmap; int /*<<< orphan*/  hs_type; } ;

/* Variables and functions */
 int CS42L42_EVENT_STAT_SEL_MASK ; 
 int CS42L42_EVENT_STAT_SEL_SHIFT ; 
 int /*<<< orphan*/  CS42L42_HS_CLAMP_DISABLE ; 
 int CS42L42_HS_CLAMP_DISABLE_MASK ; 
 int CS42L42_HS_CLAMP_DISABLE_SHIFT ; 
 int CS42L42_HS_DET_LEVEL_MASK ; 
 int CS42L42_HS_DET_LEVEL_SHIFT ; 
 int CS42L42_LATCH_TO_VP_MASK ; 
 int CS42L42_LATCH_TO_VP_SHIFT ; 
 int /*<<< orphan*/  CS42L42_MIC_DET_CTL1 ; 
 int /*<<< orphan*/  CS42L42_PLUG_INVALID ; 
 int /*<<< orphan*/  CS42L42_TIPSENSE_CTL ; 
 int CS42L42_TIP_SENSE_CTRL_MASK ; 
 int CS42L42_TIP_SENSE_CTRL_SHIFT ; 
 int CS42L42_TIP_SENSE_DEBOUNCE_MASK ; 
 int CS42L42_TIP_SENSE_DEBOUNCE_SHIFT ; 
 int CS42L42_TIP_SENSE_INV_MASK ; 
 int CS42L42_TIP_SENSE_INV_SHIFT ; 
 int /*<<< orphan*/  CS42L42_TSRS_PLUG_STATUS ; 
 char CS42L42_TS_PLUG_MASK ; 
 char CS42L42_TS_PLUG_SHIFT ; 
 char CS42L42_TS_UNPLUG_MASK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cs42l42_setup_hs_type_detect(struct cs42l42_private *cs42l42)
{
	unsigned int reg;

	cs42l42->hs_type = CS42L42_PLUG_INVALID;

	/* Latch analog controls to VP power domain */
	regmap_update_bits(cs42l42->regmap, CS42L42_MIC_DET_CTL1,
			CS42L42_LATCH_TO_VP_MASK |
			CS42L42_EVENT_STAT_SEL_MASK |
			CS42L42_HS_DET_LEVEL_MASK,
			(1 << CS42L42_LATCH_TO_VP_SHIFT) |
			(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
			(cs42l42->bias_thresholds[0] <<
			CS42L42_HS_DET_LEVEL_SHIFT));

	/* Remove ground noise-suppression clamps */
	regmap_update_bits(cs42l42->regmap,
			CS42L42_HS_CLAMP_DISABLE,
			CS42L42_HS_CLAMP_DISABLE_MASK,
			(1 << CS42L42_HS_CLAMP_DISABLE_SHIFT));

	/* Enable the tip sense circuit */
	regmap_update_bits(cs42l42->regmap, CS42L42_TIPSENSE_CTL,
			CS42L42_TIP_SENSE_CTRL_MASK |
			CS42L42_TIP_SENSE_INV_MASK |
			CS42L42_TIP_SENSE_DEBOUNCE_MASK,
			(3 << CS42L42_TIP_SENSE_CTRL_SHIFT) |
			(0 << CS42L42_TIP_SENSE_INV_SHIFT) |
			(2 << CS42L42_TIP_SENSE_DEBOUNCE_SHIFT));

	/* Save the initial status of the tip sense */
	regmap_read(cs42l42->regmap,
			  CS42L42_TSRS_PLUG_STATUS,
			  &reg);
	cs42l42->plug_state = (((char) reg) &
		      (CS42L42_TS_PLUG_MASK | CS42L42_TS_UNPLUG_MASK)) >>
		      CS42L42_TS_PLUG_SHIFT;
}