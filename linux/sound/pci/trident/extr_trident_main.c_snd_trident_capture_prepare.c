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
struct snd_trident_voice {unsigned int LBA; int isync; int isync_mark; int ESO; int isync_ESO; int FMC; int RVol; int CVol; int GVSel; int Pan; int Vol; scalar_t__ Attribute; scalar_t__ FMS; scalar_t__ Alpha; scalar_t__ EC; int /*<<< orphan*/  CTRL; scalar_t__ CSO; int /*<<< orphan*/  isync_max; int /*<<< orphan*/  spurious_threshold; int /*<<< orphan*/  Delta; TYPE_1__* memblk; } ;
struct snd_trident {int bDMAStart; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int dma_addr; int rate; int channels; int period_size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  format; struct snd_trident_voice* private_data; } ;
struct TYPE_2__ {unsigned int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEGACY_DMAR0 ; 
 int /*<<< orphan*/  LEGACY_DMAR11 ; 
 int /*<<< orphan*/  LEGACY_DMAR15 ; 
 int /*<<< orphan*/  LEGACY_DMAR4 ; 
 int /*<<< orphan*/  LEGACY_DMAR6 ; 
 int /*<<< orphan*/  T4D_SBBL_SBCL ; 
 int /*<<< orphan*/  T4D_SBDELTA_DELTA_R ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_format_signed (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_trident* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_control_mode (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_trident_convert_rate (unsigned int) ; 
 int /*<<< orphan*/  snd_trident_spurious_threshold (unsigned int,int) ; 
 int /*<<< orphan*/  snd_trident_write_voice_regs (struct snd_trident*,struct snd_trident_voice*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_trident_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_trident *trident = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_trident_voice *voice = runtime->private_data;
	unsigned int val, ESO_bytes;

	spin_lock_irq(&trident->reg_lock);

	// Initialize the channel and set channel Mode
	outb(0, TRID_REG(trident, LEGACY_DMAR15));

	// Set DMA channel operation mode register
	outb(0x54, TRID_REG(trident, LEGACY_DMAR11));

	// Set channel buffer Address, DMAR0 expects contiguous PCI memory area	
	voice->LBA = runtime->dma_addr;
	outl(voice->LBA, TRID_REG(trident, LEGACY_DMAR0));
	if (voice->memblk)
		voice->LBA = voice->memblk->offset;

	// set ESO
	ESO_bytes = snd_pcm_lib_buffer_bytes(substream) - 1;
	outb((ESO_bytes & 0x00ff0000) >> 16, TRID_REG(trident, LEGACY_DMAR6));
	outw((ESO_bytes & 0x0000ffff), TRID_REG(trident, LEGACY_DMAR4));
	ESO_bytes++;

	// Set channel sample rate, 4.12 format
	val = (((unsigned int) 48000L << 12) + (runtime->rate/2)) / runtime->rate;
	outw(val, TRID_REG(trident, T4D_SBDELTA_DELTA_R));

	// Set channel interrupt blk length
	if (snd_pcm_format_width(runtime->format) == 16) {
		val = (unsigned short) ((ESO_bytes >> 1) - 1);
	} else {
		val = (unsigned short) (ESO_bytes - 1);
	}

	outl((val << 16) | val, TRID_REG(trident, T4D_SBBL_SBCL));

	// Right now, set format and start to run captureing, 
	// continuous run loop enable.
	trident->bDMAStart = 0x19;	// 0001 1001b

	if (snd_pcm_format_width(runtime->format) == 16)
		trident->bDMAStart |= 0x80;
	if (snd_pcm_format_signed(runtime->format))
		trident->bDMAStart |= 0x20;
	if (runtime->channels > 1)
		trident->bDMAStart |= 0x40;

	// Prepare capture intr channel

	voice->Delta = snd_trident_convert_rate(runtime->rate);
	voice->spurious_threshold = snd_trident_spurious_threshold(runtime->rate, runtime->period_size);
	voice->isync = 1;
	voice->isync_mark = runtime->period_size;
	voice->isync_max = runtime->buffer_size;

	// Set voice parameters
	voice->CSO = 0;
	voice->ESO = voice->isync_ESO = (runtime->period_size * 2) + 6 - 1;
	voice->CTRL = snd_trident_control_mode(substream);
	voice->FMC = 3;
	voice->RVol = 0x7f;
	voice->CVol = 0x7f;
	voice->GVSel = 1;
	voice->Pan = 0x7f;		/* mute */
	voice->Vol = 0x3ff;		/* mute */
	voice->EC = 0;
	voice->Alpha = 0;
	voice->FMS = 0;
	voice->Attribute = 0;

	snd_trident_write_voice_regs(trident, voice);

	spin_unlock_irq(&trident->reg_lock);
	return 0;
}