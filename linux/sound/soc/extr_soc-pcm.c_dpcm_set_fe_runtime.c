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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai_driver {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; } ;
struct snd_soc_dai {struct snd_soc_dai_driver* driver; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; int /*<<< orphan*/  rates; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dpcm_init_runtime_hw (struct snd_pcm_runtime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpcm_runtime_merge_chan (struct snd_pcm_substream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpcm_runtime_merge_format (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpcm_runtime_merge_rate (struct snd_pcm_substream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpcm_set_fe_runtime(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai_driver *cpu_dai_drv = cpu_dai->driver;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dpcm_init_runtime_hw(runtime, &cpu_dai_drv->playback);
	else
		dpcm_init_runtime_hw(runtime, &cpu_dai_drv->capture);

	dpcm_runtime_merge_format(substream, &runtime->hw.formats);
	dpcm_runtime_merge_chan(substream, &runtime->hw.channels_min,
				&runtime->hw.channels_max);
	dpcm_runtime_merge_rate(substream, &runtime->hw.rates,
				&runtime->hw.rate_min, &runtime->hw.rate_max);
}