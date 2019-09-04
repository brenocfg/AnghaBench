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
struct cs42l42_private {int btn_det_event_dbnce; int* bias_thresholds; int /*<<< orphan*/  regmap; TYPE_1__* component; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L42_DET_INT2_MASK ; 
 int /*<<< orphan*/  CS42L42_DET_INT_STATUS2 ; 
 int /*<<< orphan*/  CS42L42_DET_STATUS2 ; 
 int CS42L42_EVENT_STAT_SEL_MASK ; 
 int CS42L42_EVENT_STAT_SEL_SHIFT ; 
 int CS42L42_HS_DET_LEVEL_MASK ; 
 int CS42L42_HS_DET_LEVEL_SHIFT ; 
 unsigned int CS42L42_HS_TRUE_MASK ; 
 int CS42L42_LATCH_TO_VP_MASK ; 
 int CS42L42_LATCH_TO_VP_SHIFT ; 
 int /*<<< orphan*/  CS42L42_MIC_DET_CTL1 ; 
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
 int CS42L42_NUM_BIASES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void cs42l42_handle_button_press(struct cs42l42_private *cs42l42)
{
	int bias_level;
	unsigned int detect_status;

	/* Mask button detect interrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_DET_INT2_MASK,
		CS42L42_M_DETECT_TF_MASK |
		CS42L42_M_DETECT_FT_MASK |
		CS42L42_M_HSBIAS_HIZ_MASK |
		CS42L42_M_SHORT_RLS_MASK |
		CS42L42_M_SHORT_DET_MASK,
		(1 << CS42L42_M_DETECT_TF_SHIFT) |
		(1 << CS42L42_M_DETECT_FT_SHIFT) |
		(1 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
		(1 << CS42L42_M_SHORT_RLS_SHIFT) |
		(1 << CS42L42_M_SHORT_DET_SHIFT));

	usleep_range(cs42l42->btn_det_event_dbnce * 1000,
		     cs42l42->btn_det_event_dbnce * 2000);

	/* Test all 4 level detect biases */
	bias_level = 1;
	do {
		/* Adjust button detect level sensitivity */
		regmap_update_bits(cs42l42->regmap,
			CS42L42_MIC_DET_CTL1,
			CS42L42_LATCH_TO_VP_MASK |
			CS42L42_EVENT_STAT_SEL_MASK |
			CS42L42_HS_DET_LEVEL_MASK,
			(1 << CS42L42_LATCH_TO_VP_SHIFT) |
			(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
			(cs42l42->bias_thresholds[bias_level] <<
			CS42L42_HS_DET_LEVEL_SHIFT));

		regmap_read(cs42l42->regmap, CS42L42_DET_STATUS2,
				&detect_status);
	} while ((detect_status & CS42L42_HS_TRUE_MASK) &&
		(++bias_level < CS42L42_NUM_BIASES));

	switch (bias_level) {
	case 1: /* Function C button press */
		dev_dbg(cs42l42->component->dev, "Function C button press\n");
		break;
	case 2: /* Function B button press */
		dev_dbg(cs42l42->component->dev, "Function B button press\n");
		break;
	case 3: /* Function D button press */
		dev_dbg(cs42l42->component->dev, "Function D button press\n");
		break;
	case 4: /* Function A button press */
		dev_dbg(cs42l42->component->dev, "Function A button press\n");
		break;
	}

	/* Set button detect level sensitivity back to default */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_MIC_DET_CTL1,
		CS42L42_LATCH_TO_VP_MASK |
		CS42L42_EVENT_STAT_SEL_MASK |
		CS42L42_HS_DET_LEVEL_MASK,
		(1 << CS42L42_LATCH_TO_VP_SHIFT) |
		(0 << CS42L42_EVENT_STAT_SEL_SHIFT) |
		(cs42l42->bias_thresholds[0] << CS42L42_HS_DET_LEVEL_SHIFT));

	/* Clear any button interrupts before unmasking them */
	regmap_read(cs42l42->regmap, CS42L42_DET_INT_STATUS2,
		    &detect_status);

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
}