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
struct pm8916_wcd_analog_priv {int mbhc_btn0_released; int /*<<< orphan*/  jack; struct snd_soc_component* component; scalar_t__ detect_accessory_type; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_A_MBHC_RESULT_1 ; 
 int CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  btn_mask ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mbhc_btn_release_irq_handler(int irq, void *arg)
{
	struct pm8916_wcd_analog_priv *priv = arg;

	if (priv->detect_accessory_type) {
		struct snd_soc_component *component = priv->component;
		u32 val = snd_soc_component_read32(component, CDC_A_MBHC_RESULT_1);

		/* check if its BTN0 thats released */
		if ((val != -1) && !(val & CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK))
			priv->mbhc_btn0_released = true;

	} else {
		snd_soc_jack_report(priv->jack, 0, btn_mask);
	}

	return IRQ_HANDLED;
}