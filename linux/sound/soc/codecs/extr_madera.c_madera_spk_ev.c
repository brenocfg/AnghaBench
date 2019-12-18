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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct madera_priv {struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MADERA_OUTPUT_ENABLES_1 ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int madera_check_speaker_overheat (struct madera*,int*,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int madera_spk_ev(struct snd_soc_dapm_widget *w,
		  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	bool warn, shutdown;
	int ret;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		ret = madera_check_speaker_overheat(madera, &warn, &shutdown);
		if (ret)
			return ret;

		if (shutdown) {
			dev_crit(madera->dev,
				 "Speaker not enabled due to temperature\n");
			return -EBUSY;
		}

		regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				   1 << w->shift, 1 << w->shift);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(madera->regmap, MADERA_OUTPUT_ENABLES_1,
				   1 << w->shift, 0);
		break;
	default:
		break;
	}

	return 0;
}