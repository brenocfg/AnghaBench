#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  stream; TYPE_2__* runtime; } ;
struct TYPE_4__ {TYPE_1__* status; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int EBADFD ; 
 int EPIPE ; 
 int ESTRPIPE ; 
#define  SNDRV_PCM_STATE_DRAINING 133 
#define  SNDRV_PCM_STATE_PAUSED 132 
#define  SNDRV_PCM_STATE_PREPARED 131 
#define  SNDRV_PCM_STATE_RUNNING 130 
#define  SNDRV_PCM_STATE_SUSPENDED 129 
#define  SNDRV_PCM_STATE_XRUN 128 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int snd_pcm_update_hw_ptr (struct snd_pcm_substream*) ; 

__attribute__((used)) static int do_pcm_hwsync(struct snd_pcm_substream *substream)
{
	switch (substream->runtime->status->state) {
	case SNDRV_PCM_STATE_DRAINING:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			return -EBADFD;
		/* Fall through */
	case SNDRV_PCM_STATE_RUNNING:
		return snd_pcm_update_hw_ptr(substream);
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_PAUSED:
		return 0;
	case SNDRV_PCM_STATE_SUSPENDED:
		return -ESTRPIPE;
	case SNDRV_PCM_STATE_XRUN:
		return -EPIPE;
	default:
		return -EBADFD;
	}
}