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
struct snd_tscm {int /*<<< orphan*/  rx_stream; } ;
struct snd_pcm_substream {struct snd_tscm* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  amdtp_stream_pcm_trigger (int /*<<< orphan*/ *,struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_tscm *tscm = substream->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(&tscm->rx_stream, substream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(&tscm->rx_stream, NULL);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}