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
struct snd_soc_pcm_runtime {int num_codecs; struct snd_soc_dai* codec_dai; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; } ;
struct snd_soc_dai_link {int /*<<< orphan*/  num_params; int /*<<< orphan*/  params; } ;
struct snd_soc_dai {struct snd_soc_dapm_widget* capture_widget; struct snd_soc_dapm_widget* playback_widget; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_dapm_new_pcm (struct snd_soc_card*,struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_soc_dapm_widget*,struct snd_soc_dapm_widget*) ; 

__attribute__((used)) static int soc_link_dai_widgets(struct snd_soc_card *card,
				struct snd_soc_dai_link *dai_link,
				struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dapm_widget *sink, *source;
	int ret;

	if (rtd->num_codecs > 1)
		dev_warn(card->dev, "ASoC: Multiple codecs not supported yet\n");

	/* link the DAI widgets */
	sink = codec_dai->playback_widget;
	source = cpu_dai->capture_widget;
	if (sink && source) {
		ret = snd_soc_dapm_new_pcm(card, rtd, dai_link->params,
					   dai_link->num_params,
					   source, sink);
		if (ret != 0) {
			dev_err(card->dev, "ASoC: Can't link %s to %s: %d\n",
				sink->name, source->name, ret);
			return ret;
		}
	}

	sink = cpu_dai->playback_widget;
	source = codec_dai->capture_widget;
	if (sink && source) {
		ret = snd_soc_dapm_new_pcm(card, rtd, dai_link->params,
					   dai_link->num_params,
					   source, sink);
		if (ret != 0) {
			dev_err(card->dev, "ASoC: Can't link %s to %s: %d\n",
				sink->name, source->name, ret);
			return ret;
		}
	}

	return 0;
}