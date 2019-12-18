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
struct snd_ymfpci_voice {int use; int pcm; int synth; int midi; } ;
struct snd_ymfpci {struct snd_ymfpci_voice* voices; } ;
typedef  enum snd_ymfpci_voice_type { ____Placeholder_snd_ymfpci_voice_type } snd_ymfpci_voice_type ;

/* Variables and functions */
 int ENOMEM ; 
 int YDSXG_PLAYBACK_VOICES ; 
#define  YMFPCI_MIDI 130 
#define  YMFPCI_PCM 129 
#define  YMFPCI_SYNTH 128 
 int /*<<< orphan*/  snd_ymfpci_hw_start (struct snd_ymfpci*) ; 

__attribute__((used)) static int voice_alloc(struct snd_ymfpci *chip,
		       enum snd_ymfpci_voice_type type, int pair,
		       struct snd_ymfpci_voice **rvoice)
{
	struct snd_ymfpci_voice *voice, *voice2;
	int idx;
	
	*rvoice = NULL;
	for (idx = 0; idx < YDSXG_PLAYBACK_VOICES; idx += pair ? 2 : 1) {
		voice = &chip->voices[idx];
		voice2 = pair ? &chip->voices[idx+1] : NULL;
		if (voice->use || (voice2 && voice2->use))
			continue;
		voice->use = 1;
		if (voice2)
			voice2->use = 1;
		switch (type) {
		case YMFPCI_PCM:
			voice->pcm = 1;
			if (voice2)
				voice2->pcm = 1;
			break;
		case YMFPCI_SYNTH:
			voice->synth = 1;
			break;
		case YMFPCI_MIDI:
			voice->midi = 1;
			break;
		}
		snd_ymfpci_hw_start(chip);
		if (voice2)
			snd_ymfpci_hw_start(chip);
		*rvoice = voice;
		return 0;
	}
	return -ENOMEM;
}