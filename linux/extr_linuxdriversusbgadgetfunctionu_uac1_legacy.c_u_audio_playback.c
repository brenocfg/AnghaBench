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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* status; } ;
struct gaudio_snd_dev {struct snd_pcm_substream* substream; } ;
struct gaudio {struct gaudio_snd_dev playback; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct gaudio*,char*,int) ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_PREPARE ; 
 scalar_t__ SNDRV_PCM_STATE_SUSPENDED ; 
 scalar_t__ SNDRV_PCM_STATE_XRUN ; 
 scalar_t__ bytes_to_frames (struct snd_pcm_runtime*,size_t) ; 
 scalar_t__ snd_pcm_kernel_ioctl (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pcm_kernel_write (struct snd_pcm_substream*,void*,scalar_t__) ; 

size_t u_audio_playback(struct gaudio *card, void *buf, size_t count)
{
	struct gaudio_snd_dev	*snd = &card->playback;
	struct snd_pcm_substream *substream = snd->substream;
	struct snd_pcm_runtime *runtime = substream->runtime;
	ssize_t result;
	snd_pcm_sframes_t frames;

try_again:
	if (runtime->status->state == SNDRV_PCM_STATE_XRUN ||
		runtime->status->state == SNDRV_PCM_STATE_SUSPENDED) {
		result = snd_pcm_kernel_ioctl(substream,
				SNDRV_PCM_IOCTL_PREPARE, NULL);
		if (result < 0) {
			ERROR(card, "Preparing sound card failed: %d\n",
					(int)result);
			return result;
		}
	}

	frames = bytes_to_frames(runtime, count);
	result = snd_pcm_kernel_write(snd->substream, buf, frames);
	if (result != frames) {
		ERROR(card, "Playback error: %d\n", (int)result);
		goto try_again;
	}

	return 0;
}