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
struct snd_emu10k1_voice {unsigned int number; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPF_CURRENTPITCH ; 
 int /*<<< orphan*/  CVCF ; 
 int /*<<< orphan*/  IFATN ; 
 int /*<<< orphan*/  IP ; 
 int /*<<< orphan*/  PTRX_PITCHTARGET ; 
 int /*<<< orphan*/  VTFT ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_intr_disable (struct snd_emu10k1*,unsigned int) ; 

__attribute__((used)) static void snd_emu10k1_playback_stop_voice(struct snd_emu10k1 *emu, struct snd_emu10k1_voice *evoice)
{
	unsigned int voice;

	if (evoice == NULL)
		return;
	voice = evoice->number;
	snd_emu10k1_voice_intr_disable(emu, voice);
	snd_emu10k1_ptr_write(emu, PTRX_PITCHTARGET, voice, 0);
	snd_emu10k1_ptr_write(emu, CPF_CURRENTPITCH, voice, 0);
	snd_emu10k1_ptr_write(emu, IFATN, voice, 0xffff);
	snd_emu10k1_ptr_write(emu, VTFT, voice, 0xffff);
	snd_emu10k1_ptr_write(emu, CVCF, voice, 0xffff);
	snd_emu10k1_ptr_write(emu, IP, voice, 0);
}