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
struct snd_sh_dac {int empty; int /*<<< orphan*/  processed; int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  buffer_end; int /*<<< orphan*/  buffer_begin; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  dac_audio_start_timer (struct snd_sh_dac*) ; 
 int /*<<< orphan*/  dac_audio_stop_timer (struct snd_sh_dac*) ; 
 struct snd_sh_dac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_sh_dac_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		dac_audio_start_timer(chip);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		chip->buffer_begin = chip->buffer_end = chip->data_buffer;
		chip->processed = 0;
		chip->empty = 1;
		dac_audio_stop_timer(chip);
		break;
	default:
		 return -EINVAL;
	}

	return 0;
}