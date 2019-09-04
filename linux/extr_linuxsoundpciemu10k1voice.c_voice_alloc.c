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
struct snd_emu10k1_voice {int use; int pcm; int synth; int midi; int efx; } ;
struct snd_emu10k1 {int next_free_voice; struct snd_emu10k1_voice* voices; } ;

/* Variables and functions */
#define  EMU10K1_EFX 131 
#define  EMU10K1_MIDI 130 
#define  EMU10K1_PCM 129 
#define  EMU10K1_SYNTH 128 
 int ENOMEM ; 
 int NUM_G ; 

__attribute__((used)) static int voice_alloc(struct snd_emu10k1 *emu, int type, int number,
		       struct snd_emu10k1_voice **rvoice)
{
	struct snd_emu10k1_voice *voice;
	int i, j, k, first_voice, last_voice, skip;

	*rvoice = NULL;
	first_voice = last_voice = 0;
	for (i = emu->next_free_voice, j = 0; j < NUM_G ; i += number, j += number) {
		/*
		dev_dbg(emu->card->dev, "i %d j %d next free %d!\n",
		       i, j, emu->next_free_voice);
		*/
		i %= NUM_G;

		/* stereo voices must be even/odd */
		if ((number == 2) && (i % 2)) {
			i++;
			continue;
		}
			
		skip = 0;
		for (k = 0; k < number; k++) {
			voice = &emu->voices[(i+k) % NUM_G];
			if (voice->use) {
				skip = 1;
				break;
			}
		}
		if (!skip) {
			/* dev_dbg(emu->card->dev, "allocated voice %d\n", i); */
			first_voice = i;
			last_voice = (i + number) % NUM_G;
			emu->next_free_voice = last_voice;
			break;
		}
	}
	
	if (first_voice == last_voice)
		return -ENOMEM;
	
	for (i = 0; i < number; i++) {
		voice = &emu->voices[(first_voice + i) % NUM_G];
		/*
		dev_dbg(emu->card->dev, "voice alloc - %i, %i of %i\n",
		       voice->number, idx-first_voice+1, number);
		*/
		voice->use = 1;
		switch (type) {
		case EMU10K1_PCM:
			voice->pcm = 1;
			break;
		case EMU10K1_SYNTH:
			voice->synth = 1;
			break;
		case EMU10K1_MIDI:
			voice->midi = 1;
			break;
		case EMU10K1_EFX:
			voice->efx = 1;
			break;
		}
	}
	*rvoice = &emu->voices[first_voice];
	return 0;
}