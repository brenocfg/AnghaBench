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
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct audio_substream_data* private_data; } ;
struct audio_substream_data {int /*<<< orphan*/  ch1; int /*<<< orphan*/  acp_mmio; int /*<<< orphan*/  ch2; int /*<<< orphan*/  capture_channel; int /*<<< orphan*/  bytescount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CHANNEL0 ; 
 int /*<<< orphan*/  CAP_CHANNEL1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  acp_dma_cap_channel_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_dma_cap_channel_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_dma_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int acp_dma_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_get_byte_count (struct audio_substream_data*) ; 

__attribute__((used)) static int acp_dma_trigger(struct snd_pcm_substream *substream, int cmd)
{
	int ret;

	struct snd_pcm_runtime *runtime = substream->runtime;
	struct audio_substream_data *rtd = runtime->private_data;

	if (!rtd)
		return -EINVAL;
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		rtd->bytescount = acp_get_byte_count(rtd);
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
			if (rtd->capture_channel == CAP_CHANNEL0) {
				acp_dma_cap_channel_disable(rtd->acp_mmio,
							    CAP_CHANNEL1);
				acp_dma_cap_channel_enable(rtd->acp_mmio,
							   CAP_CHANNEL0);
			}
			if (rtd->capture_channel == CAP_CHANNEL1) {
				acp_dma_cap_channel_disable(rtd->acp_mmio,
							    CAP_CHANNEL0);
				acp_dma_cap_channel_enable(rtd->acp_mmio,
							   CAP_CHANNEL1);
			}
			acp_dma_start(rtd->acp_mmio, rtd->ch1, true);
		} else {
			acp_dma_start(rtd->acp_mmio, rtd->ch1, true);
			acp_dma_start(rtd->acp_mmio, rtd->ch2, true);
		}
		ret = 0;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		acp_dma_stop(rtd->acp_mmio, rtd->ch2);
		ret = acp_dma_stop(rtd->acp_mmio, rtd->ch1);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}