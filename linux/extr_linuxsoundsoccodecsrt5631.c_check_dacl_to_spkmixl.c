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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned int RT5631_M_DAC_L_TO_SPKMIXER_L ; 
 int /*<<< orphan*/  RT5631_SPK_MIXER_CTRL ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_dacl_to_spkmixl(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	unsigned int reg;

	reg = snd_soc_component_read32(component, RT5631_SPK_MIXER_CTRL);
	return !(reg & RT5631_M_DAC_L_TO_SPKMIXER_L);
}