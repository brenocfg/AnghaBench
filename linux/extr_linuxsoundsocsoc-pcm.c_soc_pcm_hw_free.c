#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  pcm_mutex; struct snd_soc_dai** codec_dais; TYPE_2__* dai_link; int /*<<< orphan*/  pcm_subclass; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int active; int playback_active; int capture_active; TYPE_4__* driver; scalar_t__ sample_bits; scalar_t__ channels; scalar_t__ rate; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* hw_free ) (struct snd_pcm_substream*,struct snd_soc_dai*) ;} ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hw_free ) (struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dai_digital_mute (struct snd_soc_dai*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_pcm_components_hw_free (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub2 (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  stub3 (struct snd_pcm_substream*,struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai *codec_dai;
	bool playback = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	int i;

	mutex_lock_nested(&rtd->pcm_mutex, rtd->pcm_subclass);

	/* clear the corresponding DAIs parameters when going to be inactive */
	if (cpu_dai->active == 1) {
		cpu_dai->rate = 0;
		cpu_dai->channels = 0;
		cpu_dai->sample_bits = 0;
	}

	for (i = 0; i < rtd->num_codecs; i++) {
		codec_dai = rtd->codec_dais[i];
		if (codec_dai->active == 1) {
			codec_dai->rate = 0;
			codec_dai->channels = 0;
			codec_dai->sample_bits = 0;
		}
	}

	/* apply codec digital mute */
	for (i = 0; i < rtd->num_codecs; i++) {
		if ((playback && rtd->codec_dais[i]->playback_active == 1) ||
		    (!playback && rtd->codec_dais[i]->capture_active == 1))
			snd_soc_dai_digital_mute(rtd->codec_dais[i], 1,
						 substream->stream);
	}

	/* free any machine hw params */
	if (rtd->dai_link->ops->hw_free)
		rtd->dai_link->ops->hw_free(substream);

	/* free any component resources */
	soc_pcm_components_hw_free(substream, NULL);

	/* now free hw params for the DAIs  */
	for (i = 0; i < rtd->num_codecs; i++) {
		codec_dai = rtd->codec_dais[i];
		if (codec_dai->driver->ops->hw_free)
			codec_dai->driver->ops->hw_free(substream, codec_dai);
	}

	if (cpu_dai->driver->ops->hw_free)
		cpu_dai->driver->ops->hw_free(substream, cpu_dai);

	mutex_unlock(&rtd->pcm_mutex);
	return 0;
}