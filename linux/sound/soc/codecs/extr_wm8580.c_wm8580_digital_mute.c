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
 int /*<<< orphan*/  WM8580_DAC_CONTROL5 ; 
 unsigned int WM8580_DAC_CONTROL5_MUTEALL ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm8580_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_component *component = codec_dai->component;
	unsigned int reg;

	reg = snd_soc_component_read32(component, WM8580_DAC_CONTROL5);

	if (mute)
		reg |= WM8580_DAC_CONTROL5_MUTEALL;
	else
		reg &= ~WM8580_DAC_CONTROL5_MUTEALL;

	snd_soc_component_write(component, WM8580_DAC_CONTROL5, reg);

	return 0;
}