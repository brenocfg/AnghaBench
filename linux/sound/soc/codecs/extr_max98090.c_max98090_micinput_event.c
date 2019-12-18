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
struct snd_soc_dapm_widget {int /*<<< orphan*/  reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct max98090_priv {unsigned int pa1en; unsigned int pa2en; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int M98090_MIC_PA1EN_MASK ; 
 unsigned int M98090_MIC_PA1EN_SHIFT ; 
 unsigned int M98090_MIC_PA2EN_MASK ; 
 unsigned int M98090_MIC_PA2EN_SHIFT ; 
 int /*<<< orphan*/  M98090_REG_MIC1_INPUT_LEVEL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98090_micinput_event(struct snd_soc_dapm_widget *w,
				 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	unsigned int val = snd_soc_component_read32(component, w->reg);

	if (w->reg == M98090_REG_MIC1_INPUT_LEVEL)
		val = (val & M98090_MIC_PA1EN_MASK) >> M98090_MIC_PA1EN_SHIFT;
	else
		val = (val & M98090_MIC_PA2EN_MASK) >> M98090_MIC_PA2EN_SHIFT;

	if (val >= 1) {
		if (w->reg == M98090_REG_MIC1_INPUT_LEVEL) {
			max98090->pa1en = val - 1; /* Update for volatile */
		} else {
			max98090->pa2en = val - 1; /* Update for volatile */
		}
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* If turning on, set to most recently selected volume */
		if (w->reg == M98090_REG_MIC1_INPUT_LEVEL)
			val = max98090->pa1en + 1;
		else
			val = max98090->pa2en + 1;
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* If turning off, turn off */
		val = 0;
		break;
	default:
		return -EINVAL;
	}

	if (w->reg == M98090_REG_MIC1_INPUT_LEVEL)
		snd_soc_component_update_bits(component, w->reg, M98090_MIC_PA1EN_MASK,
			val << M98090_MIC_PA1EN_SHIFT);
	else
		snd_soc_component_update_bits(component, w->reg, M98090_MIC_PA2EN_MASK,
			val << M98090_MIC_PA2EN_SHIFT);

	return 0;
}