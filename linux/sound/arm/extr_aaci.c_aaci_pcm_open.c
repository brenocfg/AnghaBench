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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; struct aaci* private_data; } ;
struct TYPE_8__ {int channels_max; int fifo_size; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_4__ hw; struct aaci_runtime* private_data; } ;
struct aaci_runtime {TYPE_2__* pcm; struct snd_pcm_substream* substream; } ;
struct aaci {int fifo_depth; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  users; TYPE_3__* dev; struct aaci_runtime capture; struct aaci_runtime playback; } ;
struct TYPE_7__ {int /*<<< orphan*/ * irq; } ;
struct TYPE_6__ {TYPE_1__* r; int /*<<< orphan*/  rates; } ;
struct TYPE_5__ {scalar_t__ slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_4__ aaci_hw_info ; 
 int /*<<< orphan*/  aaci_irq ; 
 int /*<<< orphan*/  aaci_rule_channels ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aaci*) ; 
 int /*<<< orphan*/  snd_ac97_pcm_double_rate_rules (struct snd_pcm_runtime*) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aaci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 

__attribute__((used)) static int aaci_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct aaci *aaci = substream->private_data;
	struct aaci_runtime *aacirun;
	int ret = 0;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		aacirun = &aaci->playback;
	} else {
		aacirun = &aaci->capture;
	}

	aacirun->substream = substream;
	runtime->private_data = aacirun;
	runtime->hw = aaci_hw_info;
	runtime->hw.rates = aacirun->pcm->rates;
	snd_pcm_limit_hw_rates(runtime);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		runtime->hw.channels_max = 6;

		/* Add rule describing channel dependency. */
		ret = snd_pcm_hw_rule_add(substream->runtime, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  aaci_rule_channels, aaci,
					  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
		if (ret)
			return ret;

		if (aacirun->pcm->r[1].slots)
			snd_ac97_pcm_double_rate_rules(runtime);
	}

	/*
	 * ALSA wants the byte-size of the FIFOs.  As we only support
	 * 16-bit samples, this is twice the FIFO depth irrespective
	 * of whether it's in compact mode or not.
	 */
	runtime->hw.fifo_size = aaci->fifo_depth * 2;

	mutex_lock(&aaci->irq_lock);
	if (!aaci->users++) {
		ret = request_irq(aaci->dev->irq[0], aaci_irq,
			   IRQF_SHARED, DRIVER_NAME, aaci);
		if (ret != 0)
			aaci->users--;
	}
	mutex_unlock(&aaci->irq_lock);

	return ret;
}