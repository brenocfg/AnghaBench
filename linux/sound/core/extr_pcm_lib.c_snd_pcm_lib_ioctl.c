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
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  SNDRV_PCM_IOCTL1_CHANNEL_INFO 130 
#define  SNDRV_PCM_IOCTL1_FIFO_SIZE 129 
#define  SNDRV_PCM_IOCTL1_RESET 128 
 int snd_pcm_lib_ioctl_channel_info (struct snd_pcm_substream*,void*) ; 
 int snd_pcm_lib_ioctl_fifo_size (struct snd_pcm_substream*,void*) ; 
 int snd_pcm_lib_ioctl_reset (struct snd_pcm_substream*,void*) ; 

int snd_pcm_lib_ioctl(struct snd_pcm_substream *substream,
		      unsigned int cmd, void *arg)
{
	switch (cmd) {
	case SNDRV_PCM_IOCTL1_RESET:
		return snd_pcm_lib_ioctl_reset(substream, arg);
	case SNDRV_PCM_IOCTL1_CHANNEL_INFO:
		return snd_pcm_lib_ioctl_channel_info(substream, arg);
	case SNDRV_PCM_IOCTL1_FIFO_SIZE:
		return snd_pcm_lib_ioctl_fifo_size(substream, arg);
	}
	return -ENXIO;
}