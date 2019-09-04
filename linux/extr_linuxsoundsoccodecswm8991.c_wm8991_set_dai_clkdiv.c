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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8991_ADCCLK_DIV 131 
 int WM8991_ADC_CLKDIV_MASK ; 
#define  WM8991_BCLK_DIV 130 
 int WM8991_BCLK_DIV_MASK ; 
 int /*<<< orphan*/  WM8991_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8991_CLOCKING_2 ; 
#define  WM8991_DACCLK_DIV 129 
 int WM8991_DAC_CLKDIV_MASK ; 
#define  WM8991_MCLK_DIV 128 
 int WM8991_MCLK_DIV_MASK ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8991_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 reg;

	switch (div_id) {
	case WM8991_MCLK_DIV:
		reg = snd_soc_component_read32(component, WM8991_CLOCKING_2) &
		      ~WM8991_MCLK_DIV_MASK;
		snd_soc_component_write(component, WM8991_CLOCKING_2, reg | div);
		break;
	case WM8991_DACCLK_DIV:
		reg = snd_soc_component_read32(component, WM8991_CLOCKING_2) &
		      ~WM8991_DAC_CLKDIV_MASK;
		snd_soc_component_write(component, WM8991_CLOCKING_2, reg | div);
		break;
	case WM8991_ADCCLK_DIV:
		reg = snd_soc_component_read32(component, WM8991_CLOCKING_2) &
		      ~WM8991_ADC_CLKDIV_MASK;
		snd_soc_component_write(component, WM8991_CLOCKING_2, reg | div);
		break;
	case WM8991_BCLK_DIV:
		reg = snd_soc_component_read32(component, WM8991_CLOCKING_1) &
		      ~WM8991_BCLK_DIV_MASK;
		snd_soc_component_write(component, WM8991_CLOCKING_1, reg | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}