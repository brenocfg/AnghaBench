#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {int rate_max; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_3__ hw; } ;
struct pcm_substream {int active; struct snd_pcm_substream* instance; } ;
struct pcm_runtime {int /*<<< orphan*/  stream_mutex; scalar_t__ extra_freq; TYPE_2__* chip; struct pcm_substream playback; scalar_t__ panic; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_KNOT ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  constraints_extra_rates ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ pcm_hw ; 
 int snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hiface_pcm_open(struct snd_pcm_substream *alsa_sub)
{
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	struct pcm_substream *sub = NULL;
	struct snd_pcm_runtime *alsa_rt = alsa_sub->runtime;
	int ret;

	if (rt->panic)
		return -EPIPE;

	mutex_lock(&rt->stream_mutex);
	alsa_rt->hw = pcm_hw;

	if (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		sub = &rt->playback;

	if (!sub) {
		struct device *device = &rt->chip->dev->dev;
		mutex_unlock(&rt->stream_mutex);
		dev_err(device, "Invalid stream type\n");
		return -EINVAL;
	}

	if (rt->extra_freq) {
		alsa_rt->hw.rates |= SNDRV_PCM_RATE_KNOT;
		alsa_rt->hw.rate_max = 384000;

		/* explicit constraints needed as we added SNDRV_PCM_RATE_KNOT */
		ret = snd_pcm_hw_constraint_list(alsa_sub->runtime, 0,
						 SNDRV_PCM_HW_PARAM_RATE,
						 &constraints_extra_rates);
		if (ret < 0) {
			mutex_unlock(&rt->stream_mutex);
			return ret;
		}
	}

	sub->instance = alsa_sub;
	sub->active = false;
	mutex_unlock(&rt->stream_mutex);
	return 0;
}