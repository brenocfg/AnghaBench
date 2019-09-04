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
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_IOCTL_DELAY 135 
#define  SNDRV_PCM_IOCTL_DRAIN 134 
#define  SNDRV_PCM_IOCTL_DROP 133 
#define  SNDRV_PCM_IOCTL_FORWARD 132 
#define  SNDRV_PCM_IOCTL_HW_PARAMS 131 
#define  SNDRV_PCM_IOCTL_PREPARE 130 
#define  SNDRV_PCM_IOCTL_START 129 
#define  SNDRV_PCM_IOCTL_SW_PARAMS 128 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int snd_pcm_delay (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int snd_pcm_drain (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int snd_pcm_drop (struct snd_pcm_substream*) ; 
 int snd_pcm_forward (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_params (struct snd_pcm_substream*,void*) ; 
 int snd_pcm_prepare (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int snd_pcm_start_lock_irq (struct snd_pcm_substream*) ; 
 int snd_pcm_sw_params (struct snd_pcm_substream*,void*) ; 

int snd_pcm_kernel_ioctl(struct snd_pcm_substream *substream,
			 unsigned int cmd, void *arg)
{
	snd_pcm_uframes_t *frames = arg;
	snd_pcm_sframes_t result;
	
	switch (cmd) {
	case SNDRV_PCM_IOCTL_FORWARD:
	{
		/* provided only for OSS; capture-only and no value returned */
		if (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
			return -EINVAL;
		result = snd_pcm_forward(substream, *frames);
		return result < 0 ? result : 0;
	}
	case SNDRV_PCM_IOCTL_HW_PARAMS:
		return snd_pcm_hw_params(substream, arg);
	case SNDRV_PCM_IOCTL_SW_PARAMS:
		return snd_pcm_sw_params(substream, arg);
	case SNDRV_PCM_IOCTL_PREPARE:
		return snd_pcm_prepare(substream, NULL);
	case SNDRV_PCM_IOCTL_START:
		return snd_pcm_start_lock_irq(substream);
	case SNDRV_PCM_IOCTL_DRAIN:
		return snd_pcm_drain(substream, NULL);
	case SNDRV_PCM_IOCTL_DROP:
		return snd_pcm_drop(substream);
	case SNDRV_PCM_IOCTL_DELAY:
		return snd_pcm_delay(substream, frames);
	default:
		return -EINVAL;
	}
}