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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5663_priv {int codec_ver; } ;

/* Variables and functions */
#define  CODEC_VER_0 129 
#define  CODEC_VER_1 128 
 int /*<<< orphan*/  RT5663_EN_4BTN_INL_DIS ; 
 int /*<<< orphan*/  RT5663_EN_4BTN_INL_EN ; 
 int /*<<< orphan*/  RT5663_EN_4BTN_INL_MASK ; 
 int /*<<< orphan*/  RT5663_EN_IRQ_INLINE_BYP ; 
 int /*<<< orphan*/  RT5663_EN_IRQ_INLINE_MASK ; 
 int /*<<< orphan*/  RT5663_EN_IRQ_INLINE_NOR ; 
 int /*<<< orphan*/  RT5663_IL_CMD_6 ; 
 int /*<<< orphan*/  RT5663_IRQ_2 ; 
 int /*<<< orphan*/  RT5663_IRQ_3 ; 
 int /*<<< orphan*/  RT5663_RESET_4BTN_INL_MASK ; 
 int /*<<< orphan*/  RT5663_RESET_4BTN_INL_NOR ; 
 int /*<<< orphan*/  RT5663_RESET_4BTN_INL_RESET ; 
 int /*<<< orphan*/  RT5663_V2_EN_IRQ_INLINE_BYP ; 
 int /*<<< orphan*/  RT5663_V2_EN_IRQ_INLINE_MASK ; 
 int /*<<< orphan*/  RT5663_V2_EN_IRQ_INLINE_NOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5663_enable_push_button_irq(struct snd_soc_component *component,
	bool enable)
{
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);

	if (enable) {
		snd_soc_component_update_bits(component, RT5663_IL_CMD_6,
			RT5663_EN_4BTN_INL_MASK, RT5663_EN_4BTN_INL_EN);
		/* reset in-line command */
		snd_soc_component_update_bits(component, RT5663_IL_CMD_6,
			RT5663_RESET_4BTN_INL_MASK,
			RT5663_RESET_4BTN_INL_RESET);
		snd_soc_component_update_bits(component, RT5663_IL_CMD_6,
			RT5663_RESET_4BTN_INL_MASK,
			RT5663_RESET_4BTN_INL_NOR);
		switch (rt5663->codec_ver) {
		case CODEC_VER_1:
			snd_soc_component_update_bits(component, RT5663_IRQ_3,
				RT5663_V2_EN_IRQ_INLINE_MASK,
				RT5663_V2_EN_IRQ_INLINE_NOR);
			break;
		case CODEC_VER_0:
			snd_soc_component_update_bits(component, RT5663_IRQ_2,
				RT5663_EN_IRQ_INLINE_MASK,
				RT5663_EN_IRQ_INLINE_NOR);
			break;
		default:
			dev_err(component->dev, "Unknown CODEC Version\n");
		}
	} else {
		switch (rt5663->codec_ver) {
		case CODEC_VER_1:
			snd_soc_component_update_bits(component, RT5663_IRQ_3,
				RT5663_V2_EN_IRQ_INLINE_MASK,
				RT5663_V2_EN_IRQ_INLINE_BYP);
			break;
		case CODEC_VER_0:
			snd_soc_component_update_bits(component, RT5663_IRQ_2,
				RT5663_EN_IRQ_INLINE_MASK,
				RT5663_EN_IRQ_INLINE_BYP);
			break;
		default:
			dev_err(component->dev, "Unknown CODEC Version\n");
		}
		snd_soc_component_update_bits(component, RT5663_IL_CMD_6,
			RT5663_EN_4BTN_INL_MASK, RT5663_EN_4BTN_INL_DIS);
		/* reset in-line command */
		snd_soc_component_update_bits(component, RT5663_IL_CMD_6,
			RT5663_RESET_4BTN_INL_MASK,
			RT5663_RESET_4BTN_INL_RESET);
		snd_soc_component_update_bits(component, RT5663_IL_CMD_6,
			RT5663_RESET_4BTN_INL_MASK,
			RT5663_RESET_4BTN_INL_NOR);
	}
}