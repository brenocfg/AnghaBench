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
struct snd_pcsp {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int pcsp_start_playing (struct snd_pcsp*) ; 
 int /*<<< orphan*/  pcsp_stop_playing (struct snd_pcsp*) ; 
 struct snd_pcsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcsp_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_pcsp *chip = snd_pcm_substream_chip(substream);
#if PCSP_DEBUG
	printk(KERN_INFO "PCSP: trigger called\n");
#endif
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		return pcsp_start_playing(chip);
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		pcsp_stop_playing(chip);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}