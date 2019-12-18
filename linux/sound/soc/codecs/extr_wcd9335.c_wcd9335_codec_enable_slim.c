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
struct TYPE_2__ {int /*<<< orphan*/  chs; } ;
struct wcd_slim_codec_dai_data {TYPE_1__ sconfig; } ;
struct wcd9335_codec {struct wcd_slim_codec_dai_data* dai; } ;
struct snd_soc_dapm_widget {size_t shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct wcd9335_codec* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd9335_codec_enable_int_port (struct wcd_slim_codec_dai_data*,struct snd_soc_component*) ; 

__attribute__((used)) static int wcd9335_codec_enable_slim(struct snd_soc_dapm_widget *w,
				       struct snd_kcontrol *kc,
				       int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	struct wcd9335_codec *wcd = snd_soc_component_get_drvdata(comp);
	struct wcd_slim_codec_dai_data *dai = &wcd->dai[w->shift];

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wcd9335_codec_enable_int_port(dai, comp);
		break;
	case SND_SOC_DAPM_POST_PMD:
		kfree(dai->sconfig.chs);

		break;
	}

	return 0;
}