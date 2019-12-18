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
struct snd_info_entry {struct snd_emu10k1* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_emu10k1_voice {int /*<<< orphan*/  midi; int /*<<< orphan*/  synth; int /*<<< orphan*/  efx; int /*<<< orphan*/  pcm; int /*<<< orphan*/  use; } ;
struct snd_emu10k1 {struct snd_emu10k1_voice* voices; } ;

/* Variables and functions */
 int NUM_G ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_emu10k1_proc_voices_read(struct snd_info_entry *entry, 
				  struct snd_info_buffer *buffer)
{
	struct snd_emu10k1 *emu = entry->private_data;
	struct snd_emu10k1_voice *voice;
	int idx;
	
	snd_iprintf(buffer, "ch\tuse\tpcm\tefx\tsynth\tmidi\n");
	for (idx = 0; idx < NUM_G; idx++) {
		voice = &emu->voices[idx];
		snd_iprintf(buffer, "%i\t%i\t%i\t%i\t%i\t%i\n",
			idx,
			voice->use,
			voice->pcm,
			voice->efx,
			voice->synth,
			voice->midi);
	}
}