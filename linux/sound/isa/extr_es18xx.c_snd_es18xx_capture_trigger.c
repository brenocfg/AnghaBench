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
struct snd_es18xx {int active; } ;

/* Variables and functions */
 int ADC1 ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_es18xx_write (struct snd_es18xx*,int,int) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es18xx_capture_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
        struct snd_es18xx *chip = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (chip->active & ADC1)
			return 0;
		chip->active |= ADC1;
                /* Start DMA */
                snd_es18xx_write(chip, 0xB8, 0x0f);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (!(chip->active & ADC1))
			return 0;
		chip->active &= ~ADC1;
                /* Stop DMA */
                snd_es18xx_write(chip, 0xB8, 0x00);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}