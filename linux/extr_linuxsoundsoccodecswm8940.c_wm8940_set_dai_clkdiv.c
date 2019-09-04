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
#define  WM8940_BCLKDIV 130 
 int /*<<< orphan*/  WM8940_CLOCK ; 
 int /*<<< orphan*/  WM8940_GPIO ; 
#define  WM8940_MCLKDIV 129 
#define  WM8940_OPCLKDIV 128 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8940_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 reg;
	int ret = 0;

	switch (div_id) {
	case WM8940_BCLKDIV:
		reg = snd_soc_component_read32(component, WM8940_CLOCK) & 0xFFE3;
		ret = snd_soc_component_write(component, WM8940_CLOCK, reg | (div << 2));
		break;
	case WM8940_MCLKDIV:
		reg = snd_soc_component_read32(component, WM8940_CLOCK) & 0xFF1F;
		ret = snd_soc_component_write(component, WM8940_CLOCK, reg | (div << 5));
		break;
	case WM8940_OPCLKDIV:
		reg = snd_soc_component_read32(component, WM8940_GPIO) & 0xFFCF;
		ret = snd_soc_component_write(component, WM8940_GPIO, reg | (div << 4));
		break;
	}
	return ret;
}