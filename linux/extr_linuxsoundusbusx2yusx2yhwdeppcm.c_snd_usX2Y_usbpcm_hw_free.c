#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_usX2Y_substream {TYPE_4__* usX2Y; int /*<<< orphan*/  state; TYPE_3__* pcm_substream; } ;
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_usX2Y_substream* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  pcm_mutex; struct snd_usX2Y_substream** subs; } ;
struct TYPE_7__ {TYPE_2__* runtime; } ;
struct TYPE_6__ {TYPE_1__* status; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_PREPARED ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*,struct snd_pcm_substream*) ; 
 scalar_t__ state_PREPARED ; 
 int /*<<< orphan*/  state_STOPPED ; 
 int /*<<< orphan*/  usX2Y_usbpcm_urbs_release (struct snd_usX2Y_substream*) ; 

__attribute__((used)) static int snd_usX2Y_usbpcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_usX2Y_substream *subs = runtime->private_data,
		*cap_subs2 = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE + 2];
	mutex_lock(&subs->usX2Y->pcm_mutex);
	snd_printdd("snd_usX2Y_usbpcm_hw_free(%p)\n", substream);

	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
		struct snd_usX2Y_substream *cap_subs = subs->usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE];
		atomic_set(&subs->state, state_STOPPED);
		usX2Y_usbpcm_urbs_release(subs);
		if (!cap_subs->pcm_substream ||
		    !cap_subs->pcm_substream->runtime ||
		    !cap_subs->pcm_substream->runtime->status ||
		    cap_subs->pcm_substream->runtime->status->state < SNDRV_PCM_STATE_PREPARED) {
			atomic_set(&cap_subs->state, state_STOPPED);
			if (NULL != cap_subs2)
				atomic_set(&cap_subs2->state, state_STOPPED);
			usX2Y_usbpcm_urbs_release(cap_subs);
			if (NULL != cap_subs2)
				usX2Y_usbpcm_urbs_release(cap_subs2);
		}
	} else {
		struct snd_usX2Y_substream *playback_subs = subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
		if (atomic_read(&playback_subs->state) < state_PREPARED) {
			atomic_set(&subs->state, state_STOPPED);
			if (NULL != cap_subs2)
				atomic_set(&cap_subs2->state, state_STOPPED);
			usX2Y_usbpcm_urbs_release(subs);
			if (NULL != cap_subs2)
				usX2Y_usbpcm_urbs_release(cap_subs2);
		}
	}
	mutex_unlock(&subs->usX2Y->pcm_mutex);
	return snd_pcm_lib_free_pages(substream);
}