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
#define  WM8580_CLKOUTSRC 134 
#define  WM8580_CLKSRC_MCLK 133 
#define  WM8580_CLKSRC_NONE 132 
#define  WM8580_CLKSRC_OSC 131 
#define  WM8580_CLKSRC_PLLA 130 
#define  WM8580_CLKSRC_PLLB 129 
#define  WM8580_MCLK 128 
 int /*<<< orphan*/  WM8580_PLLB4 ; 
 unsigned int WM8580_PLLB4_CLKOUTSRC_MASK ; 
 unsigned int WM8580_PLLB4_CLKOUTSRC_OSCCLK ; 
 unsigned int WM8580_PLLB4_CLKOUTSRC_PLLACLK ; 
 unsigned int WM8580_PLLB4_CLKOUTSRC_PLLBCLK ; 
 unsigned int WM8580_PLLB4_MCLKOUTSRC_MASK ; 
 unsigned int WM8580_PLLB4_MCLKOUTSRC_OSC ; 
 unsigned int WM8580_PLLB4_MCLKOUTSRC_PLLA ; 
 unsigned int WM8580_PLLB4_MCLKOUTSRC_PLLB ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm8580_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;
	unsigned int reg;

	switch (div_id) {
	case WM8580_MCLK:
		reg = snd_soc_component_read32(component, WM8580_PLLB4);
		reg &= ~WM8580_PLLB4_MCLKOUTSRC_MASK;

		switch (div) {
		case WM8580_CLKSRC_MCLK:
			/* Input */
			break;

		case WM8580_CLKSRC_PLLA:
			reg |= WM8580_PLLB4_MCLKOUTSRC_PLLA;
			break;
		case WM8580_CLKSRC_PLLB:
			reg |= WM8580_PLLB4_MCLKOUTSRC_PLLB;
			break;

		case WM8580_CLKSRC_OSC:
			reg |= WM8580_PLLB4_MCLKOUTSRC_OSC;
			break;

		default:
			return -EINVAL;
		}
		snd_soc_component_write(component, WM8580_PLLB4, reg);
		break;

	case WM8580_CLKOUTSRC:
		reg = snd_soc_component_read32(component, WM8580_PLLB4);
		reg &= ~WM8580_PLLB4_CLKOUTSRC_MASK;

		switch (div) {
		case WM8580_CLKSRC_NONE:
			break;

		case WM8580_CLKSRC_PLLA:
			reg |= WM8580_PLLB4_CLKOUTSRC_PLLACLK;
			break;

		case WM8580_CLKSRC_PLLB:
			reg |= WM8580_PLLB4_CLKOUTSRC_PLLBCLK;
			break;

		case WM8580_CLKSRC_OSC:
			reg |= WM8580_PLLB4_CLKOUTSRC_OSCCLK;
			break;

		default:
			return -EINVAL;
		}
		snd_soc_component_write(component, WM8580_PLLB4, reg);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}