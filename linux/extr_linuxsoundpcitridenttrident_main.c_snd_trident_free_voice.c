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
struct snd_trident_voice {void (* private_free ) (struct snd_trident_voice*) ;int /*<<< orphan*/ * extra; int /*<<< orphan*/ * substream; int /*<<< orphan*/ * sample_ops; scalar_t__ spdif; scalar_t__ capture; scalar_t__ midi; scalar_t__ synth; scalar_t__ pcm; scalar_t__ use; int /*<<< orphan*/  number; int /*<<< orphan*/ * private_data; } ;
struct snd_trident {int /*<<< orphan*/  voice_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_trident_clear_voices (struct snd_trident*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_trident_free_pcm_channel (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_trident_free_synth_channel (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_trident_free_voice(struct snd_trident * trident, struct snd_trident_voice *voice)
{
	unsigned long flags;
	void (*private_free)(struct snd_trident_voice *);

	if (voice == NULL || !voice->use)
		return;
	snd_trident_clear_voices(trident, voice->number, voice->number);
	spin_lock_irqsave(&trident->voice_alloc, flags);
	private_free = voice->private_free;
	voice->private_free = NULL;
	voice->private_data = NULL;
	if (voice->pcm)
		snd_trident_free_pcm_channel(trident, voice->number);
	if (voice->synth)
		snd_trident_free_synth_channel(trident, voice->number);
	voice->use = voice->pcm = voice->synth = voice->midi = 0;
	voice->capture = voice->spdif = 0;
	voice->sample_ops = NULL;
	voice->substream = NULL;
	voice->extra = NULL;
	spin_unlock_irqrestore(&trident->voice_alloc, flags);
	if (private_free)
		private_free(voice);
}