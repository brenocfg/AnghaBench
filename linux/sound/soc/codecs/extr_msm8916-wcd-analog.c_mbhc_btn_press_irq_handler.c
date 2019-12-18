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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct pm8916_wcd_analog_priv {int /*<<< orphan*/  jack; int /*<<< orphan*/  detect_accessory_type; struct snd_soc_component* component; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_A_MBHC_RESULT_1 ; 
 int CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SND_JACK_BTN_0 ; 
 int /*<<< orphan*/  SND_JACK_BTN_1 ; 
 int /*<<< orphan*/  SND_JACK_BTN_2 ; 
 int /*<<< orphan*/  SND_JACK_BTN_3 ; 
 int /*<<< orphan*/  SND_JACK_BTN_4 ; 
 int /*<<< orphan*/  btn_mask ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mbhc_btn_press_irq_handler(int irq, void *arg)
{
	struct pm8916_wcd_analog_priv *priv = arg;
	struct snd_soc_component *component = priv->component;
	u32 btn_result;

	btn_result = snd_soc_component_read32(component, CDC_A_MBHC_RESULT_1) &
				  CDC_A_MBHC_RESULT_1_BTN_RESULT_MASK;

	switch (btn_result) {
	case 0xf:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_4, btn_mask);
		break;
	case 0x7:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_3, btn_mask);
		break;
	case 0x3:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_2, btn_mask);
		break;
	case 0x1:
		snd_soc_jack_report(priv->jack, SND_JACK_BTN_1, btn_mask);
		break;
	case 0x0:
		/* handle BTN_0 specially for type detection */
		if (!priv->detect_accessory_type)
			snd_soc_jack_report(priv->jack,
					    SND_JACK_BTN_0, btn_mask);
		break;
	default:
		dev_err(component->dev,
			"Unexpected button press result (%x)", btn_result);
		break;
	}

	return IRQ_HANDLED;
}