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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5659_4BTN_IL_CMD_1 ; 
 int /*<<< orphan*/  RT5659_4BTN_IL_CMD_2 ; 
 int /*<<< orphan*/  RT5659_4BTN_IL_DIS ; 
 int /*<<< orphan*/  RT5659_4BTN_IL_EN ; 
 int /*<<< orphan*/  RT5659_4BTN_IL_MASK ; 
 int /*<<< orphan*/  RT5659_IL_IRQ_DIS ; 
 int /*<<< orphan*/  RT5659_IL_IRQ_EN ; 
 int /*<<< orphan*/  RT5659_IL_IRQ_MASK ; 
 int /*<<< orphan*/  RT5659_IRQ_CTRL_2 ; 
 int /*<<< orphan*/  RT5659_PWR_ANLG_2 ; 
 int /*<<< orphan*/  RT5659_PWR_MB1 ; 
 int /*<<< orphan*/  RT5659_PWR_MIC_DET ; 
 int /*<<< orphan*/  RT5659_PWR_VOL ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void rt5659_enable_push_button_irq(struct snd_soc_component *component,
	bool enable)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (enable) {
		snd_soc_component_write(component, RT5659_4BTN_IL_CMD_1, 0x000b);

		/* MICBIAS1 and Mic Det Power for button detect*/
		snd_soc_dapm_force_enable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_force_enable_pin(dapm,
			"Mic Det Power");
		snd_soc_dapm_sync(dapm);

		snd_soc_component_update_bits(component, RT5659_PWR_ANLG_2,
			RT5659_PWR_MB1, RT5659_PWR_MB1);
		snd_soc_component_update_bits(component, RT5659_PWR_VOL,
			RT5659_PWR_MIC_DET, RT5659_PWR_MIC_DET);

		snd_soc_component_update_bits(component, RT5659_IRQ_CTRL_2,
				RT5659_IL_IRQ_MASK, RT5659_IL_IRQ_EN);
		snd_soc_component_update_bits(component, RT5659_4BTN_IL_CMD_2,
				RT5659_4BTN_IL_MASK, RT5659_4BTN_IL_EN);
	} else {
		snd_soc_component_update_bits(component, RT5659_4BTN_IL_CMD_2,
				RT5659_4BTN_IL_MASK, RT5659_4BTN_IL_DIS);
		snd_soc_component_update_bits(component, RT5659_IRQ_CTRL_2,
				RT5659_IL_IRQ_MASK, RT5659_IL_IRQ_DIS);
		/* MICBIAS1 and Mic Det Power for button detect*/
		snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
		snd_soc_dapm_disable_pin(dapm, "Mic Det Power");
		snd_soc_dapm_sync(dapm);
	}
}