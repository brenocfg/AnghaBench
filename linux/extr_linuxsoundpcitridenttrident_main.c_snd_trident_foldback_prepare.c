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
struct snd_trident_voice {int ESO; int Delta; int FMC; int RVol; int CVol; int GVSel; int Pan; int Vol; int number; int isync2; int isync_mark; scalar_t__ Attribute; scalar_t__ FMS; scalar_t__ Alpha; scalar_t__ EC; int /*<<< orphan*/  CTRL; scalar_t__ CSO; int /*<<< orphan*/  LBA; int /*<<< orphan*/  spurious_threshold; scalar_t__ foldback_chan; TYPE_1__* memblk; struct snd_trident_voice* extra; } ;
struct snd_trident {scalar_t__ device; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int buffer_size; int period_size; int /*<<< orphan*/  dma_addr; struct snd_trident_voice* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ T4D_RCI ; 
 scalar_t__ TRIDENT_DEVICE_ID_SI7018 ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 struct snd_trident* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_control_mode (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_spurious_threshold (int,int) ; 
 int /*<<< orphan*/  snd_trident_write_voice_regs (struct snd_trident*,struct snd_trident_voice*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_trident_foldback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_trident *trident = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_trident_voice *voice = runtime->private_data;
	struct snd_trident_voice *evoice = voice->extra;

	spin_lock_irq(&trident->reg_lock);

	/* Set channel buffer Address */
	if (voice->memblk)
		voice->LBA = voice->memblk->offset;
	else
		voice->LBA = runtime->dma_addr;

	/* set target ESO for channel */
	voice->ESO = runtime->buffer_size - 1;	/* in samples */

	/* set sample rate */
	voice->Delta = 0x1000;
	voice->spurious_threshold = snd_trident_spurious_threshold(48000, runtime->period_size);

	voice->CSO = 0;
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 3;
	voice->RVol = 0x7f;
	voice->CVol = 0x7f;
	voice->GVSel = 1;
	voice->Pan = 0x7f;	/* mute */
	voice->Vol = 0x3ff;	/* mute */
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;
	voice->Attribute = 0;

	/* set up capture channel */
	outb(((voice->number & 0x3f) | 0x80), TRID_REG(trident, T4D_RCI + voice->foldback_chan));

	snd_trident_write_voice_regs(trident, voice);

	if (evoice != NULL) {
		evoice->Delta = voice->Delta;
		evoice->spurious_threshold = voice->spurious_threshold;
		evoice->LBA = voice->LBA;
		evoice->CSO = 0;
		evoice->ESO = (runtime->period_size * 2) + 4 - 1; /* in samples */
		evoice->CTRL = voice->CTRL;
		evoice->FMC = 3;
		evoice->GVSel = trident->device == TRIDENT_DEVICE_ID_SI7018 ? 0 : 1;
		evoice->EC = 0;
		evoice->Alpha = 0;
		evoice->FMS = 0;
		evoice->Vol = 0x3ff;			/* mute */
		evoice->RVol = evoice->CVol = 0x7f;	/* mute */
		evoice->Pan = 0x7f;			/* mute */
		evoice->Attribute = 0;
		snd_trident_write_voice_regs(trident, evoice);
		evoice->isync2 = 1;
		evoice->isync_mark = runtime->period_size;
		evoice->ESO = (runtime->period_size * 2) - 1;
	}

	spin_unlock_irq(&trident->reg_lock);
	return 0;
}