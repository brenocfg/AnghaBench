#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct snd_kcontrol {int dummy; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_INTERRUPT_RAW_STATUS_3 ; 
 int /*<<< orphan*/  ARIZONA_OUTPUT_ENABLES_1 ; 
 int ARIZONA_SPK_OVERHEAT_STS ; 
 int EBUSY ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int arizona_out_ev (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_spk_ev(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *kcontrol,
			  int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona *arizona = dev_get_drvdata(component->dev->parent);
	int val;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		val = snd_soc_component_read32(component,
					       ARIZONA_INTERRUPT_RAW_STATUS_3);
		if (val & ARIZONA_SPK_OVERHEAT_STS) {
			dev_crit(arizona->dev,
				 "Speaker not enabled due to temperature\n");
			return -EBUSY;
		}

		regmap_update_bits_async(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 1 << w->shift, 1 << w->shift);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits_async(arizona->regmap,
					 ARIZONA_OUTPUT_ENABLES_1,
					 1 << w->shift, 0);
		break;
	default:
		break;
	}

	return arizona_out_ev(w, kcontrol, event);
}