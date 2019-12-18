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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8900_ADC_CLKDIV 134 
#define  WM8900_ADC_LRCLK 133 
#define  WM8900_BCLK_DIV 132 
#define  WM8900_DAC_CLKDIV 131 
#define  WM8900_DAC_LRCLK 130 
#define  WM8900_LRCLK_MODE 129 
 int /*<<< orphan*/  WM8900_LRC_MASK ; 
#define  WM8900_OPCLK_DIV 128 
 int /*<<< orphan*/  WM8900_REG_AUDIO3 ; 
 int /*<<< orphan*/  WM8900_REG_AUDIO4 ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING1 ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING1_BCLK_MASK ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING1_OPCLK_MASK ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING2 ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING2_ADC_CLKDIV ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING2_DAC_CLKDIV ; 
 int /*<<< orphan*/  WM8900_REG_DACCTRL ; 
 int /*<<< orphan*/  WM8900_REG_DACCTRL_AIF_LRCLKRATE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8900_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;

	switch (div_id) {
	case WM8900_BCLK_DIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
				    WM8900_REG_CLOCKING1_BCLK_MASK, div);
		break;
	case WM8900_OPCLK_DIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
				    WM8900_REG_CLOCKING1_OPCLK_MASK, div);
		break;
	case WM8900_DAC_LRCLK:
		snd_soc_component_update_bits(component, WM8900_REG_AUDIO4,
				    WM8900_LRC_MASK, div);
		break;
	case WM8900_ADC_LRCLK:
		snd_soc_component_update_bits(component, WM8900_REG_AUDIO3,
				    WM8900_LRC_MASK, div);
		break;
	case WM8900_DAC_CLKDIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING2,
				    WM8900_REG_CLOCKING2_DAC_CLKDIV, div);
		break;
	case WM8900_ADC_CLKDIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING2,
				    WM8900_REG_CLOCKING2_ADC_CLKDIV, div);
		break;
	case WM8900_LRCLK_MODE:
		snd_soc_component_update_bits(component, WM8900_REG_DACCTRL,
				    WM8900_REG_DACCTRL_AIF_LRCLKRATE, div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}