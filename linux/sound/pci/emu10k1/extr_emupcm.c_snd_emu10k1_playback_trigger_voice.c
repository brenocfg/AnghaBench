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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  rate; } ;
struct snd_emu10k1_voice {unsigned int number; TYPE_2__* epcm; } ;
struct snd_emu10k1 {TYPE_1__* card_capabilities; } ;
struct TYPE_4__ {scalar_t__ type; struct snd_pcm_substream* substream; } ;
struct TYPE_3__ {scalar_t__ emu_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPF_CURRENTPITCH ; 
 int /*<<< orphan*/  IP ; 
 unsigned int PITCH_48000 ; 
 scalar_t__ PLAYBACK_EFX ; 
 int /*<<< orphan*/  PTRX_PITCHTARGET ; 
 unsigned int emu10k1_calc_pitch_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int snd_emu10k1_rate_to_pitch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_intr_enable (struct snd_emu10k1*,unsigned int) ; 

__attribute__((used)) static void snd_emu10k1_playback_trigger_voice(struct snd_emu10k1 *emu, struct snd_emu10k1_voice *evoice, int master, int extra)
{
	struct snd_pcm_substream *substream;
	struct snd_pcm_runtime *runtime;
	unsigned int voice, pitch, pitch_target;

	if (evoice == NULL)	/* skip second voice for mono */
		return;
	substream = evoice->epcm->substream;
	runtime = substream->runtime;
	voice = evoice->number;

	pitch = snd_emu10k1_rate_to_pitch(runtime->rate) >> 8;
	if (emu->card_capabilities->emu_model)
		pitch_target = PITCH_48000; /* Disable interpolators on emu1010 card */
	else 
		pitch_target = emu10k1_calc_pitch_target(runtime->rate);
	snd_emu10k1_ptr_write(emu, PTRX_PITCHTARGET, voice, pitch_target);
	if (master || evoice->epcm->type == PLAYBACK_EFX)
		snd_emu10k1_ptr_write(emu, CPF_CURRENTPITCH, voice, pitch_target);
	snd_emu10k1_ptr_write(emu, IP, voice, pitch);
	if (extra)
		snd_emu10k1_voice_intr_enable(emu, voice);
}