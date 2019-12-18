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
struct snd_pcm_channel_info {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_IOCTL1_CHANNEL_INFO 129 
#define  SNDRV_PCM_IOCTL1_RESET 128 
 int snd_hdspm_channel_info (struct snd_pcm_substream*,struct snd_pcm_channel_info*) ; 
 int snd_hdspm_reset (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_ioctl (struct snd_pcm_substream*,unsigned int,void*) ; 

__attribute__((used)) static int snd_hdspm_ioctl(struct snd_pcm_substream *substream,
		unsigned int cmd, void *arg)
{
	switch (cmd) {
	case SNDRV_PCM_IOCTL1_RESET:
		return snd_hdspm_reset(substream);

	case SNDRV_PCM_IOCTL1_CHANNEL_INFO:
		{
			struct snd_pcm_channel_info *info = arg;
			return snd_hdspm_channel_info(substream, info);
		}
	default:
		break;
	}

	return snd_pcm_lib_ioctl(substream, cmd, arg);
}