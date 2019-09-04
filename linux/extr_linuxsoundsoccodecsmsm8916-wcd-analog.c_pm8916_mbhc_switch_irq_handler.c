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
struct pm8916_wcd_analog_priv {int mbhc_btn0_released; int detect_accessory_type; int /*<<< orphan*/  jack; struct snd_soc_component* component; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_A_MBHC_DET_CTL_1 ; 
 int CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_MASK ; 
 int CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_SHIFT ; 
 int /*<<< orphan*/  CDC_A_MICB_2_EN ; 
 int CDC_A_MICB_2_EN_ENABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  hs_jack_mask ; 
 int /*<<< orphan*/  pm8916_mbhc_configure_bias (struct pm8916_wcd_analog_priv*,int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pm8916_mbhc_switch_irq_handler(int irq, void *arg)
{
	struct pm8916_wcd_analog_priv *priv = arg;
	struct snd_soc_component *component = priv->component;
	bool ins = false;

	if (snd_soc_component_read32(component, CDC_A_MBHC_DET_CTL_1) &
				CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_MASK)
		ins = true;

	/* Set the detection type appropriately */
	snd_soc_component_update_bits(component, CDC_A_MBHC_DET_CTL_1,
			    CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_MASK,
			    (!ins << CDC_A_MBHC_DET_CTL_MECH_DET_TYPE_SHIFT));


	if (ins) { /* hs insertion */
		bool micbias_enabled = false;

		if (snd_soc_component_read32(component, CDC_A_MICB_2_EN) &
				CDC_A_MICB_2_EN_ENABLE)
			micbias_enabled = true;

		pm8916_mbhc_configure_bias(priv, micbias_enabled);

		/*
		 * if only a btn0 press event is receive just before
		 * insert event then its a 3 pole headphone else if
		 * both press and release event received then its
		 * a headset.
		 */
		if (priv->mbhc_btn0_released)
			snd_soc_jack_report(priv->jack,
					    SND_JACK_HEADSET, hs_jack_mask);
		else
			snd_soc_jack_report(priv->jack,
					    SND_JACK_HEADPHONE, hs_jack_mask);

		priv->detect_accessory_type = false;

	} else { /* removal */
		snd_soc_jack_report(priv->jack, 0, hs_jack_mask);
		priv->detect_accessory_type = true;
		priv->mbhc_btn0_released = false;
	}

	return IRQ_HANDLED;
}