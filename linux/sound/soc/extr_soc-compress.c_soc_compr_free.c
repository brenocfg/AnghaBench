#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int pop_wait; TYPE_5__* card; int /*<<< orphan*/  pmdown_time; int /*<<< orphan*/  delayed_work; TYPE_2__* dai_link; struct snd_soc_dai* codec_dai; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_4__* driver; scalar_t__ rate; int /*<<< orphan*/  active; } ;
struct snd_compr_stream {int /*<<< orphan*/  direction; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  pcm_mutex; int /*<<< orphan*/  pcm_subclass; } ;
struct TYPE_9__ {TYPE_3__* cops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* shutdown ) (struct snd_compr_stream*,struct snd_soc_dai*) ;} ;
struct TYPE_7__ {TYPE_1__* compr_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* shutdown ) (struct snd_compr_stream*) ;} ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_COMPRESS_PLAYBACK ; 
 int /*<<< orphan*/  SND_SOC_DAPM_STREAM_STOP ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_digital_mute (struct snd_soc_dai*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_stream_event (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_runtime_deactivate (struct snd_soc_pcm_runtime*,int) ; 
 scalar_t__ snd_soc_runtime_ignore_pmdown_time (struct snd_soc_pcm_runtime*) ; 
 int /*<<< orphan*/  soc_compr_components_free (struct snd_compr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_compr_stream*) ; 
 int /*<<< orphan*/  stub2 (struct snd_compr_stream*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int soc_compr_free(struct snd_compr_stream *cstream)
{
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	int stream;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	if (cstream->direction == SND_COMPRESS_PLAYBACK)
		stream = SNDRV_PCM_STREAM_PLAYBACK;
	else
		stream = SNDRV_PCM_STREAM_CAPTURE;

	snd_soc_runtime_deactivate(rtd, stream);

	snd_soc_dai_digital_mute(codec_dai, 1, cstream->direction);

	if (!cpu_dai->active)
		cpu_dai->rate = 0;

	if (!codec_dai->active)
		codec_dai->rate = 0;

	if (rtd->dai_link->compr_ops && rtd->dai_link->compr_ops->shutdown)
		rtd->dai_link->compr_ops->shutdown(cstream);

	soc_compr_components_free(cstream, NULL);

	if (cpu_dai->driver->cops && cpu_dai->driver->cops->shutdown)
		cpu_dai->driver->cops->shutdown(cstream, cpu_dai);

	if (cstream->direction == SND_COMPRESS_PLAYBACK) {
		if (snd_soc_runtime_ignore_pmdown_time(rtd)) {
			snd_soc_dapm_stream_event(rtd,
						  SNDRV_PCM_STREAM_PLAYBACK,
						  SND_SOC_DAPM_STREAM_STOP);
		} else {
			rtd->pop_wait = 1;
			queue_delayed_work(system_power_efficient_wq,
					   &rtd->delayed_work,
					   msecs_to_jiffies(rtd->pmdown_time));
		}
	} else {
		/* capture streams can be powered down now */
		snd_soc_dapm_stream_event(rtd,
					  SNDRV_PCM_STREAM_CAPTURE,
					  SND_SOC_DAPM_STREAM_STOP);
	}

	mutex_unlock(&rtd->card->pcm_mutex);
	return 0;
}