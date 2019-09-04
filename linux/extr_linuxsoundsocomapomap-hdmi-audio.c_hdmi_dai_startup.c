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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct hdmi_audio_data {int /*<<< orphan*/  current_stream_lock; struct snd_pcm_substream* current_stream; int /*<<< orphan*/  dssdev; TYPE_1__* ops; int /*<<< orphan*/  dma_data; } ;
struct TYPE_2__ {int (* audio_startup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 struct hdmi_audio_data* card_drvdata_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hdmi_dai_abort ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_hw_constraint_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dai_set_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_dai_startup(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	struct hdmi_audio_data *ad = card_drvdata_substream(substream);
	int ret;
	/*
	 * Make sure that the period bytes are multiple of the DMA packet size.
	 * Largest packet size we use is 32 32-bit words = 128 bytes
	 */
	ret = snd_pcm_hw_constraint_step(substream->runtime, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 128);
	if (ret < 0) {
		dev_err(dai->dev, "Could not apply period constraint: %d\n",
			ret);
		return ret;
	}
	ret = snd_pcm_hw_constraint_step(substream->runtime, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 128);
	if (ret < 0) {
		dev_err(dai->dev, "Could not apply buffer constraint: %d\n",
			ret);
		return ret;
	}

	snd_soc_dai_set_dma_data(dai, substream, &ad->dma_data);

	mutex_lock(&ad->current_stream_lock);
	ad->current_stream = substream;
	mutex_unlock(&ad->current_stream_lock);

	ret = ad->ops->audio_startup(ad->dssdev, hdmi_dai_abort);

	if (ret) {
		mutex_lock(&ad->current_stream_lock);
		ad->current_stream = NULL;
		mutex_unlock(&ad->current_stream_lock);
	}

	return ret;
}