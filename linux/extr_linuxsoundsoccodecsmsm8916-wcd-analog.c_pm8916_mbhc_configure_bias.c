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
typedef  int u32 ;
struct snd_soc_component {int dummy; } ;
struct pm8916_wcd_analog_priv {int* vref_btn_micb; int* vref_btn_cs; struct snd_soc_component* component; } ;

/* Variables and functions */
 int CDC_A_MBHC_BTN0_ZDET_CTL_0 ; 
 int CDC_A_MBHC_BTN_VREF_COARSE_SHIFT ; 
 int CDC_A_MBHC_BTN_VREF_FINE_SHIFT ; 
 int /*<<< orphan*/  CDC_A_MBHC_BTN_VREF_MASK ; 
 int CDC_A_MBHC_FSM_CTL ; 
 int CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_I_100UA ; 
 int /*<<< orphan*/  CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_MASK ; 
 int CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN ; 
 int /*<<< orphan*/  CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN_MASK ; 
 int CDC_A_MICB_1_INT_RBIAS ; 
 int CDC_A_MICB_2_EN ; 
 int /*<<< orphan*/  CDC_A_MICB_2_PULL_DOWN_EN_MASK ; 
 int MBHC_MAX_BUTTONS ; 
 int MICB_1_INT_TX2_INT_RBIAS_EN_ENABLE ; 
 int /*<<< orphan*/  MICB_1_INT_TX2_INT_RBIAS_EN_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pm8916_mbhc_configure_bias(struct pm8916_wcd_analog_priv *priv,
				      bool micbias2_enabled)
{
	struct snd_soc_component *component = priv->component;
	u32 coarse, fine, reg_val, reg_addr;
	int *vrefs, i;

	if (!micbias2_enabled) { /* use internal 100uA Current source */
		/* Enable internal 2.2k Internal Rbias Resistor */
		snd_soc_component_update_bits(component, CDC_A_MICB_1_INT_RBIAS,
				    MICB_1_INT_TX2_INT_RBIAS_EN_MASK,
				    MICB_1_INT_TX2_INT_RBIAS_EN_ENABLE);
		/* Remove pull down on MIC BIAS2 */
		snd_soc_component_update_bits(component, CDC_A_MICB_2_EN,
				   CDC_A_MICB_2_PULL_DOWN_EN_MASK,
				   0);
		/* enable 100uA internal current source */
		snd_soc_component_update_bits(component, CDC_A_MBHC_FSM_CTL,
				    CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_MASK,
				    CDC_A_MBHC_FSM_CTL_BTN_ISRC_CTRL_I_100UA);
	}
	snd_soc_component_update_bits(component, CDC_A_MBHC_FSM_CTL,
			CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN_MASK,
			CDC_A_MBHC_FSM_CTL_MBHC_FSM_EN);

	if (micbias2_enabled)
		vrefs = &priv->vref_btn_micb[0];
	else
		vrefs = &priv->vref_btn_cs[0];

	/* program vref ranges for all the buttons */
	reg_addr = CDC_A_MBHC_BTN0_ZDET_CTL_0;
	for (i = 0; i <  MBHC_MAX_BUTTONS; i++) {
		/* split mv in to coarse parts of 100mv & fine parts of 12mv */
		coarse = (vrefs[i] / 100);
		fine = ((vrefs[i] % 100) / 12);
		reg_val = (coarse << CDC_A_MBHC_BTN_VREF_COARSE_SHIFT) |
			 (fine << CDC_A_MBHC_BTN_VREF_FINE_SHIFT);
		snd_soc_component_update_bits(component, reg_addr,
			       CDC_A_MBHC_BTN_VREF_MASK,
			       reg_val);
		reg_addr++;
	}

	return 0;
}