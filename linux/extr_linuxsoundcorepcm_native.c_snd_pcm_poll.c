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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_2__* control; TYPE_1__* status; int /*<<< orphan*/  sleep; } ;
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct file {struct snd_pcm_file* private_data; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {int /*<<< orphan*/  avail_min; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
#define  SNDRV_PCM_STATE_DRAINING 131 
#define  SNDRV_PCM_STATE_PAUSED 130 
#define  SNDRV_PCM_STATE_PREPARED 129 
#define  SNDRV_PCM_STATE_RUNNING 128 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_avail (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static __poll_t snd_pcm_poll(struct file *file, poll_table *wait)
{
	struct snd_pcm_file *pcm_file;
	struct snd_pcm_substream *substream;
	struct snd_pcm_runtime *runtime;
	__poll_t mask, ok;
	snd_pcm_uframes_t avail;

	pcm_file = file->private_data;

	substream = pcm_file->substream;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ok = EPOLLOUT | EPOLLWRNORM;
	else
		ok = EPOLLIN | EPOLLRDNORM;
	if (PCM_RUNTIME_CHECK(substream))
		return ok | EPOLLERR;

	runtime = substream->runtime;
	poll_wait(file, &runtime->sleep, wait);

	mask = 0;
	snd_pcm_stream_lock_irq(substream);
	avail = snd_pcm_avail(substream);
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_RUNNING:
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_PAUSED:
		if (avail >= runtime->control->avail_min)
			mask = ok;
		break;
	case SNDRV_PCM_STATE_DRAINING:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
			mask = ok;
			if (!avail)
				mask |= EPOLLERR;
		}
		break;
	default:
		mask = ok | EPOLLERR;
		break;
	}
	snd_pcm_stream_unlock_irq(substream);
	return mask;
}