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
struct snd_kcontrol {int dummy; } ;
struct max98504_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  pcm_rx_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX98504_PCM_RX_ENABLE ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max98504_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98504_pcm_rx_ev(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	struct max98504_priv *max98504 = snd_soc_component_get_drvdata(c);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		regmap_write(max98504->regmap, MAX98504_PCM_RX_ENABLE,
			     max98504->pcm_rx_channels);
		break;
	case SND_SOC_DAPM_POST_PMD:
		regmap_write(max98504->regmap, MAX98504_PCM_RX_ENABLE, 0);
		break;
	}

	return 0;
}