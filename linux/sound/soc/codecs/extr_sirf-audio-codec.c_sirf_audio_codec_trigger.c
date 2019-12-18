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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct sirf_audio_codec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_IC_CODEC_CTRL0 ; 
 int EINVAL ; 
 int IC_HSLEN ; 
 int IC_HSREN ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  sirf_audio_codec_rx_disable (struct sirf_audio_codec*) ; 
 int /*<<< orphan*/  sirf_audio_codec_rx_enable (struct sirf_audio_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirf_audio_codec_tx_disable (struct sirf_audio_codec*) ; 
 int /*<<< orphan*/  sirf_audio_codec_tx_enable (struct sirf_audio_codec*) ; 
 struct sirf_audio_codec* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sirf_audio_codec_trigger(struct snd_pcm_substream *substream,
		int cmd,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct sirf_audio_codec *sirf_audio_codec = snd_soc_component_get_drvdata(component);
	int playback = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	/*
	 * This is a workaround, When stop playback,
	 * need disable HP amp, avoid the current noise.
	 */
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (playback) {
			snd_soc_component_update_bits(component, AUDIO_IC_CODEC_CTRL0,
				IC_HSLEN | IC_HSREN, 0);
			sirf_audio_codec_tx_disable(sirf_audio_codec);
		} else
			sirf_audio_codec_rx_disable(sirf_audio_codec);
		break;
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (playback) {
			sirf_audio_codec_tx_enable(sirf_audio_codec);
			snd_soc_component_update_bits(component, AUDIO_IC_CODEC_CTRL0,
				IC_HSLEN | IC_HSREN, IC_HSLEN | IC_HSREN);
		} else
			sirf_audio_codec_rx_enable(sirf_audio_codec,
				substream->runtime->channels);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}