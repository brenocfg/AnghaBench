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
struct sun4i_codec {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct sun4i_codec* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_codec_start_capture (struct sun4i_codec*) ; 
 int /*<<< orphan*/  sun4i_codec_start_playback (struct sun4i_codec*) ; 
 int /*<<< orphan*/  sun4i_codec_stop_capture (struct sun4i_codec*) ; 
 int /*<<< orphan*/  sun4i_codec_stop_playback (struct sun4i_codec*) ; 

__attribute__((used)) static int sun4i_codec_trigger(struct snd_pcm_substream *substream, int cmd,
			       struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct sun4i_codec *scodec = snd_soc_card_get_drvdata(rtd->card);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sun4i_codec_start_playback(scodec);
		else
			sun4i_codec_start_capture(scodec);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sun4i_codec_stop_playback(scodec);
		else
			sun4i_codec_stop_capture(scodec);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}