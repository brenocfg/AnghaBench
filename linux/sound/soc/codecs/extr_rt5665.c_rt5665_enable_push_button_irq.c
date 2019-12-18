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
 int /*<<< orphan*/  RT5665_4BTN_IL_CMD_1 ; 
 int /*<<< orphan*/  RT5665_4BTN_IL_CMD_2 ; 
 int RT5665_4BTN_IL_DIS ; 
 int RT5665_4BTN_IL_EN ; 
 int RT5665_4BTN_IL_MASK ; 
 int RT5665_4BTN_IL_NOR ; 
 int RT5665_4BTN_IL_RST ; 
 int RT5665_4BTN_IL_RST_MASK ; 
 int /*<<< orphan*/  RT5665_IL_CMD_1 ; 
 int RT5665_IL_IRQ_DIS ; 
 int RT5665_IL_IRQ_EN ; 
 int RT5665_IL_IRQ_MASK ; 
 int /*<<< orphan*/  RT5665_IRQ_CTRL_3 ; 
 int /*<<< orphan*/  RT5665_SAR_IL_CMD_9 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt5665_enable_push_button_irq(struct snd_soc_component *component,
	bool enable)
{
	if (enable) {
		snd_soc_component_write(component, RT5665_4BTN_IL_CMD_1, 0x0003);
		snd_soc_component_update_bits(component, RT5665_SAR_IL_CMD_9, 0x1, 0x1);
		snd_soc_component_write(component, RT5665_IL_CMD_1, 0x0048);
		snd_soc_component_update_bits(component, RT5665_4BTN_IL_CMD_2,
				RT5665_4BTN_IL_MASK | RT5665_4BTN_IL_RST_MASK,
				RT5665_4BTN_IL_EN | RT5665_4BTN_IL_NOR);
		snd_soc_component_update_bits(component, RT5665_IRQ_CTRL_3,
				RT5665_IL_IRQ_MASK, RT5665_IL_IRQ_EN);
	} else {
		snd_soc_component_update_bits(component, RT5665_IRQ_CTRL_3,
				RT5665_IL_IRQ_MASK, RT5665_IL_IRQ_DIS);
		snd_soc_component_update_bits(component, RT5665_4BTN_IL_CMD_2,
				RT5665_4BTN_IL_MASK, RT5665_4BTN_IL_DIS);
		snd_soc_component_update_bits(component, RT5665_4BTN_IL_CMD_2,
				RT5665_4BTN_IL_RST_MASK, RT5665_4BTN_IL_RST);
	}
}