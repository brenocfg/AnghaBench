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
struct emu10k1x_voice {struct emu10k1x_pcm* epcm; } ;
struct emu10k1x_pcm {int /*<<< orphan*/ * substream; } ;
struct emu10k1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_emu10k1x_pcm_interrupt(struct emu10k1x *emu, struct emu10k1x_voice *voice)
{
	struct emu10k1x_pcm *epcm;

	if ((epcm = voice->epcm) == NULL)
		return;
	if (epcm->substream == NULL)
		return;
#if 0
	dev_info(emu->card->dev,
		 "IRQ: position = 0x%x, period = 0x%x, size = 0x%x\n",
		   epcm->substream->ops->pointer(epcm->substream),
		   snd_pcm_lib_period_bytes(epcm->substream),
		   snd_pcm_lib_buffer_bytes(epcm->substream));
#endif
	snd_pcm_period_elapsed(epcm->substream);
}