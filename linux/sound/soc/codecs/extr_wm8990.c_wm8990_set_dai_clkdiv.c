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
#define  WM8990_ADCCLK_DIV 131 
 int /*<<< orphan*/  WM8990_ADC_CLKDIV_MASK ; 
#define  WM8990_BCLK_DIV 130 
 int /*<<< orphan*/  WM8990_BCLK_DIV_MASK ; 
 int /*<<< orphan*/  WM8990_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8990_CLOCKING_2 ; 
#define  WM8990_DACCLK_DIV 129 
 int /*<<< orphan*/  WM8990_DAC_CLKDIV_MASK ; 
#define  WM8990_MCLK_DIV 128 
 int /*<<< orphan*/  WM8990_MCLK_DIV_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8990_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;

	switch (div_id) {
	case WM8990_MCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_MCLK_DIV_MASK, div);
		break;
	case WM8990_DACCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_DAC_CLKDIV_MASK, div);
		break;
	case WM8990_ADCCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_ADC_CLKDIV_MASK, div);
		break;
	case WM8990_BCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_1,
				    WM8990_BCLK_DIV_MASK, div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}