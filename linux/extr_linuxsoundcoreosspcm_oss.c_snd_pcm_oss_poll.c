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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {scalar_t__ trigger; } ;
struct snd_pcm_runtime {TYPE_2__ oss; TYPE_1__* status; int /*<<< orphan*/  sleep; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;
struct file {struct snd_pcm_oss_file* private_data; } ;
typedef  scalar_t__ snd_pcm_state_t ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  ofile ;
typedef  int __poll_t ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  PCM_ENABLE_INPUT ; 
 scalar_t__ SNDRV_PCM_STATE_DRAINING ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  memset (struct snd_pcm_oss_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pcm_oss_capture_ready (struct snd_pcm_substream*) ; 
 scalar_t__ snd_pcm_oss_playback_ready (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_oss_set_trigger (struct snd_pcm_oss_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static __poll_t snd_pcm_oss_poll(struct file *file, poll_table * wait)
{
	struct snd_pcm_oss_file *pcm_oss_file;
	__poll_t mask;
	struct snd_pcm_substream *psubstream = NULL, *csubstream = NULL;
	
	pcm_oss_file = file->private_data;

	psubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	csubstream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];

	mask = 0;
	if (psubstream != NULL) {
		struct snd_pcm_runtime *runtime = psubstream->runtime;
		poll_wait(file, &runtime->sleep, wait);
		snd_pcm_stream_lock_irq(psubstream);
		if (runtime->status->state != SNDRV_PCM_STATE_DRAINING &&
		    (runtime->status->state != SNDRV_PCM_STATE_RUNNING ||
		     snd_pcm_oss_playback_ready(psubstream)))
			mask |= EPOLLOUT | EPOLLWRNORM;
		snd_pcm_stream_unlock_irq(psubstream);
	}
	if (csubstream != NULL) {
		struct snd_pcm_runtime *runtime = csubstream->runtime;
		snd_pcm_state_t ostate;
		poll_wait(file, &runtime->sleep, wait);
		snd_pcm_stream_lock_irq(csubstream);
		if ((ostate = runtime->status->state) != SNDRV_PCM_STATE_RUNNING ||
		    snd_pcm_oss_capture_ready(csubstream))
			mask |= EPOLLIN | EPOLLRDNORM;
		snd_pcm_stream_unlock_irq(csubstream);
		if (ostate != SNDRV_PCM_STATE_RUNNING && runtime->oss.trigger) {
			struct snd_pcm_oss_file ofile;
			memset(&ofile, 0, sizeof(ofile));
			ofile.streams[SNDRV_PCM_STREAM_CAPTURE] = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
			runtime->oss.trigger = 0;
			snd_pcm_oss_set_trigger(&ofile, PCM_ENABLE_INPUT);
		}
	}

	return mask;
}