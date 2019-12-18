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
struct snd_emu10k1 {TYPE_2__* pcm_capture_substream; } ;
struct TYPE_4__ {TYPE_1__* runtime; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 unsigned int IPR_ADCBUFHALFFULL ; 
 scalar_t__ SNDRV_PCM_MODE_FRAME ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_2__*) ; 

__attribute__((used)) static void snd_emu10k1_pcm_ac97adc_interrupt(struct snd_emu10k1 *emu,
					      unsigned int status)
{
#if 0
	if (status & IPR_ADCBUFHALFFULL) {
		if (emu->pcm_capture_substream->runtime->mode == SNDRV_PCM_MODE_FRAME)
			return;
	}
#endif
	snd_pcm_period_elapsed(emu->pcm_capture_substream);
}