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
struct snd_pcm_substream {int f_flags; TYPE_2__* runtime; } ;
struct file {int f_flags; } ;
struct TYPE_4__ {TYPE_1__* status; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
#define  SNDRV_PCM_STATE_PAUSED 129 
 int /*<<< orphan*/  SNDRV_PCM_STATE_SETUP ; 
#define  SNDRV_PCM_STATE_SUSPENDED 128 
 int snd_pcm_action_nonatomic (int /*<<< orphan*/ *,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_action_prepare ; 
 int /*<<< orphan*/  snd_pcm_pause (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stop (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_prepare(struct snd_pcm_substream *substream,
			   struct file *file)
{
	int f_flags;

	if (file)
		f_flags = file->f_flags;
	else
		f_flags = substream->f_flags;

	snd_pcm_stream_lock_irq(substream);
	switch (substream->runtime->status->state) {
	case SNDRV_PCM_STATE_PAUSED:
		snd_pcm_pause(substream, 0);
		/* fallthru */
	case SNDRV_PCM_STATE_SUSPENDED:
		snd_pcm_stop(substream, SNDRV_PCM_STATE_SETUP);
		break;
	}
	snd_pcm_stream_unlock_irq(substream);

	return snd_pcm_action_nonatomic(&snd_pcm_action_prepare,
					substream, f_flags);
}