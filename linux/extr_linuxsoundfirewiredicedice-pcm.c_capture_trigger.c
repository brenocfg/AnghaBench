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
struct snd_pcm_substream {TYPE_1__* pcm; struct snd_dice* private_data; } ;
struct snd_dice {struct amdtp_stream* tx_stream; } ;
struct amdtp_stream {int dummy; } ;
struct TYPE_2__ {size_t device; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  amdtp_stream_pcm_trigger (struct amdtp_stream*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_dice *dice = substream->private_data;
	struct amdtp_stream *stream = &dice->tx_stream[substream->pcm->device];

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		amdtp_stream_pcm_trigger(stream, substream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		amdtp_stream_pcm_trigger(stream, NULL);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}