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
struct snd_emu10k1_voice {int /*<<< orphan*/  number; int /*<<< orphan*/ * epcm; scalar_t__ efx; scalar_t__ midi; scalar_t__ synth; scalar_t__ pcm; scalar_t__ use; int /*<<< orphan*/ * interrupt; } ;
struct snd_emu10k1 {int /*<<< orphan*/  voice_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_init (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_emu10k1_voice_free(struct snd_emu10k1 *emu,
			   struct snd_emu10k1_voice *pvoice)
{
	unsigned long flags;

	if (snd_BUG_ON(!pvoice))
		return -EINVAL;
	spin_lock_irqsave(&emu->voice_lock, flags);
	pvoice->interrupt = NULL;
	pvoice->use = pvoice->pcm = pvoice->synth = pvoice->midi = pvoice->efx = 0;
	pvoice->epcm = NULL;
	snd_emu10k1_voice_init(emu, pvoice->number);
	spin_unlock_irqrestore(&emu->voice_lock, flags);
	return 0;
}