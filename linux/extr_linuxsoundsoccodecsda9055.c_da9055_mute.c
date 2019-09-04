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
 int /*<<< orphan*/  DA9055_DAC_L_CTRL ; 
 int /*<<< orphan*/  DA9055_DAC_L_MUTE_EN ; 
 int /*<<< orphan*/  DA9055_DAC_R_CTRL ; 
 int /*<<< orphan*/  DA9055_DAC_R_MUTE_EN ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9055_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;

	if (mute) {
		snd_soc_component_update_bits(component, DA9055_DAC_L_CTRL,
				    DA9055_DAC_L_MUTE_EN, DA9055_DAC_L_MUTE_EN);
		snd_soc_component_update_bits(component, DA9055_DAC_R_CTRL,
				    DA9055_DAC_R_MUTE_EN, DA9055_DAC_R_MUTE_EN);
	} else {
		snd_soc_component_update_bits(component, DA9055_DAC_L_CTRL,
				    DA9055_DAC_L_MUTE_EN, 0);
		snd_soc_component_update_bits(component, DA9055_DAC_R_CTRL,
				    DA9055_DAC_R_MUTE_EN, 0);
	}

	return 0;
}