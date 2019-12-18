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
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct loopback_pcm* private_data; } ;
struct loopback_pcm {void* last_jiffies; int /*<<< orphan*/  last_drift; int /*<<< orphan*/  pcm_rate_shift; struct loopback_cable* cable; } ;
struct loopback_cable {int running; int pause; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 void* jiffies ; 
 int /*<<< orphan*/  loopback_active_notify (struct loopback_pcm*) ; 
 int loopback_check_format (struct loopback_cable*,int) ; 
 int /*<<< orphan*/  loopback_timer_start (struct loopback_pcm*) ; 
 int /*<<< orphan*/  loopback_timer_stop (struct loopback_pcm*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loopback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct loopback_pcm *dpcm = runtime->private_data;
	struct loopback_cable *cable = dpcm->cable;
	int err, stream = 1 << substream->stream;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		err = loopback_check_format(cable, substream->stream);
		if (err < 0)
			return err;
		dpcm->last_jiffies = jiffies;
		dpcm->pcm_rate_shift = 0;
		dpcm->last_drift = 0;
		spin_lock(&cable->lock);	
		cable->running |= stream;
		cable->pause &= ~stream;
		loopback_timer_start(dpcm);
		spin_unlock(&cable->lock);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notify(dpcm);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		spin_lock(&cable->lock);	
		cable->running &= ~stream;
		cable->pause &= ~stream;
		loopback_timer_stop(dpcm);
		spin_unlock(&cable->lock);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notify(dpcm);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		spin_lock(&cable->lock);	
		cable->pause |= stream;
		loopback_timer_stop(dpcm);
		spin_unlock(&cable->lock);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notify(dpcm);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		spin_lock(&cable->lock);
		dpcm->last_jiffies = jiffies;
		cable->pause &= ~stream;
		loopback_timer_start(dpcm);
		spin_unlock(&cable->lock);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notify(dpcm);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}