#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_trident_voice {int use; int pcm; int synth; int client; int port; int /*<<< orphan*/ * memblk; int /*<<< orphan*/ * substream; scalar_t__ spdif; scalar_t__ capture; } ;
struct TYPE_2__ {struct snd_trident_voice* voices; } ;
struct snd_trident {int /*<<< orphan*/  voice_alloc; TYPE_1__ synth; } ;

/* Variables and functions */
 int SNDRV_TRIDENT_VOICE_TYPE_MIDI ; 
 int SNDRV_TRIDENT_VOICE_TYPE_PCM ; 
 int SNDRV_TRIDENT_VOICE_TYPE_SYNTH ; 
 int snd_trident_allocate_pcm_channel (struct snd_trident*) ; 
 int snd_trident_allocate_synth_channel (struct snd_trident*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct snd_trident_voice *snd_trident_alloc_voice(struct snd_trident * trident, int type, int client, int port)
{
	struct snd_trident_voice *pvoice;
	unsigned long flags;
	int idx;

	spin_lock_irqsave(&trident->voice_alloc, flags);
	if (type == SNDRV_TRIDENT_VOICE_TYPE_PCM) {
		idx = snd_trident_allocate_pcm_channel(trident);
		if(idx < 0) {
			spin_unlock_irqrestore(&trident->voice_alloc, flags);
			return NULL;
		}
		pvoice = &trident->synth.voices[idx];
		pvoice->use = 1;
		pvoice->pcm = 1;
		pvoice->capture = 0;
		pvoice->spdif = 0;
		pvoice->memblk = NULL;
		pvoice->substream = NULL;
		spin_unlock_irqrestore(&trident->voice_alloc, flags);
		return pvoice;
	}
	if (type == SNDRV_TRIDENT_VOICE_TYPE_SYNTH) {
		idx = snd_trident_allocate_synth_channel(trident);
		if(idx < 0) {
			spin_unlock_irqrestore(&trident->voice_alloc, flags);
			return NULL;
		}
		pvoice = &trident->synth.voices[idx];
		pvoice->use = 1;
		pvoice->synth = 1;
		pvoice->client = client;
		pvoice->port = port;
		pvoice->memblk = NULL;
		spin_unlock_irqrestore(&trident->voice_alloc, flags);
		return pvoice;
	}
	if (type == SNDRV_TRIDENT_VOICE_TYPE_MIDI) {
	}
	spin_unlock_irqrestore(&trident->voice_alloc, flags);
	return NULL;
}