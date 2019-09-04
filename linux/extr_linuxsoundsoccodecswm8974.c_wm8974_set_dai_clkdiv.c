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
#define  WM8974_BCLKDIV 130 
 int /*<<< orphan*/  WM8974_CLOCK ; 
 int /*<<< orphan*/  WM8974_GPIO ; 
#define  WM8974_MCLKDIV 129 
#define  WM8974_OPCLKDIV 128 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8974_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 reg;

	switch (div_id) {
	case WM8974_OPCLKDIV:
		reg = snd_soc_component_read32(component, WM8974_GPIO) & 0x1cf;
		snd_soc_component_write(component, WM8974_GPIO, reg | div);
		break;
	case WM8974_MCLKDIV:
		reg = snd_soc_component_read32(component, WM8974_CLOCK) & 0x11f;
		snd_soc_component_write(component, WM8974_CLOCK, reg | div);
		break;
	case WM8974_BCLKDIV:
		reg = snd_soc_component_read32(component, WM8974_CLOCK) & 0x1e3;
		snd_soc_component_write(component, WM8974_CLOCK, reg | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}