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
 int /*<<< orphan*/  AC97_CENTER_LFE_MASTER ; 
 int /*<<< orphan*/  AC97_HANDSET_RATE ; 
 int /*<<< orphan*/  AC97_LINE1_LEVEL ; 
 int EINVAL ; 
#define  WM9713_CLKA_MULT 134 
#define  WM9713_CLKB_MULT 133 
#define  WM9713_HIFI_DIV 132 
#define  WM9713_HIFI_PLL_DIV 131 
#define  WM9713_PCMBCLK_DIV 130 
#define  WM9713_PCMCLK_DIV 129 
#define  WM9713_PCMCLK_PLL_DIV 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm9713_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;

	switch (div_id) {
	case WM9713_PCMCLK_DIV:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0f00, div);
		break;
	case WM9713_CLKA_MULT:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0002, div);
		break;
	case WM9713_CLKB_MULT:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x0004, div);
		break;
	case WM9713_HIFI_DIV:
		snd_soc_component_update_bits(component, AC97_HANDSET_RATE, 0x7000, div);
		break;
	case WM9713_PCMBCLK_DIV:
		snd_soc_component_update_bits(component, AC97_CENTER_LFE_MASTER, 0x0e00, div);
		break;
	case WM9713_PCMCLK_PLL_DIV:
		snd_soc_component_update_bits(component, AC97_LINE1_LEVEL,
				    0x007f, div | 0x60);
		break;
	case WM9713_HIFI_PLL_DIV:
		snd_soc_component_update_bits(component, AC97_LINE1_LEVEL,
				    0x007f, div | 0x70);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}