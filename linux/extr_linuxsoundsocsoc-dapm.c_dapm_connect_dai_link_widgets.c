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
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  dev; struct snd_soc_dai** codec_dais; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; } ;
struct snd_soc_dai {TYPE_1__* component; struct snd_soc_dapm_widget* capture_widget; struct snd_soc_dapm_widget* playback_widget; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_path (int /*<<< orphan*/ *,struct snd_soc_dapm_widget*,struct snd_soc_dapm_widget*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dapm_connect_dai_link_widgets(struct snd_soc_card *card,
					  struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dapm_widget *sink, *source;
	int i;

	for (i = 0; i < rtd->num_codecs; i++) {
		struct snd_soc_dai *codec_dai = rtd->codec_dais[i];

		/* connect BE DAI playback if widgets are valid */
		if (codec_dai->playback_widget && cpu_dai->playback_widget) {
			source = cpu_dai->playback_widget;
			sink = codec_dai->playback_widget;
			dev_dbg(rtd->dev, "connected DAI link %s:%s -> %s:%s\n",
				cpu_dai->component->name, source->name,
				codec_dai->component->name, sink->name);

			snd_soc_dapm_add_path(&card->dapm, source, sink,
				NULL, NULL);
		}

		/* connect BE DAI capture if widgets are valid */
		if (codec_dai->capture_widget && cpu_dai->capture_widget) {
			source = codec_dai->capture_widget;
			sink = cpu_dai->capture_widget;
			dev_dbg(rtd->dev, "connected DAI link %s:%s -> %s:%s\n",
				codec_dai->component->name, source->name,
				cpu_dai->component->name, sink->name);

			snd_soc_dapm_add_path(&card->dapm, source, sink,
				NULL, NULL);
		}
	}
}