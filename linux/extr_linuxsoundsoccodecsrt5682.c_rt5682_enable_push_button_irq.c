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

/* Variables and functions */
 int /*<<< orphan*/  RT5682_4BTN_IL_CMD_2 ; 
 int RT5682_4BTN_IL_DIS ; 
 int RT5682_4BTN_IL_EN ; 
 int RT5682_4BTN_IL_MASK ; 
 int RT5682_4BTN_IL_NOR ; 
 int RT5682_4BTN_IL_RST ; 
 int RT5682_4BTN_IL_RST_MASK ; 
 int /*<<< orphan*/  RT5682_IL_CMD_1 ; 
 int RT5682_IL_IRQ_DIS ; 
 int RT5682_IL_IRQ_EN ; 
 int RT5682_IL_IRQ_MASK ; 
 int /*<<< orphan*/  RT5682_IRQ_CTRL_3 ; 
 int RT5682_SAR_BUTT_DET_DIS ; 
 int RT5682_SAR_BUTT_DET_EN ; 
 int RT5682_SAR_BUTT_DET_MASK ; 
 int /*<<< orphan*/  RT5682_SAR_IL_CMD_1 ; 
 int /*<<< orphan*/  RT5682_SAR_IL_CMD_13 ; 
 int RT5682_SAR_SOUR_BTN ; 
 int RT5682_SAR_SOUR_MASK ; 
 int RT5682_SAR_SOUR_TYPE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt5682_enable_push_button_irq(struct snd_soc_component *component,
		bool enable)
{
	if (enable) {
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_1,
			RT5682_SAR_BUTT_DET_MASK, RT5682_SAR_BUTT_DET_EN);
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_13,
			RT5682_SAR_SOUR_MASK, RT5682_SAR_SOUR_BTN);
		snd_soc_component_write(component, RT5682_IL_CMD_1, 0x0040);
		snd_soc_component_update_bits(component, RT5682_4BTN_IL_CMD_2,
			RT5682_4BTN_IL_MASK | RT5682_4BTN_IL_RST_MASK,
			RT5682_4BTN_IL_EN | RT5682_4BTN_IL_NOR);
		snd_soc_component_update_bits(component, RT5682_IRQ_CTRL_3,
			RT5682_IL_IRQ_MASK, RT5682_IL_IRQ_EN);
	} else {
		snd_soc_component_update_bits(component, RT5682_IRQ_CTRL_3,
			RT5682_IL_IRQ_MASK, RT5682_IL_IRQ_DIS);
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_1,
			RT5682_SAR_BUTT_DET_MASK, RT5682_SAR_BUTT_DET_DIS);
		snd_soc_component_update_bits(component, RT5682_4BTN_IL_CMD_2,
			RT5682_4BTN_IL_MASK, RT5682_4BTN_IL_DIS);
		snd_soc_component_update_bits(component, RT5682_4BTN_IL_CMD_2,
			RT5682_4BTN_IL_RST_MASK, RT5682_4BTN_IL_RST);
		snd_soc_component_update_bits(component, RT5682_SAR_IL_CMD_13,
			RT5682_SAR_SOUR_MASK, RT5682_SAR_SOUR_TYPE);
	}
}