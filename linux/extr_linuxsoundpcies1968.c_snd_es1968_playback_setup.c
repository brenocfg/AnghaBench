#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_runtime {int rate; } ;
struct esschan {int dma_size; int wav_shift; int fmt; int* apu; int* base; int* apu_mode; TYPE_2__* memory; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct es1968 {int /*<<< orphan*/  reg_lock; scalar_t__ io_port; TYPE_3__ dma; } ;
struct TYPE_4__ {int addr; } ;
struct TYPE_5__ {TYPE_1__ buf; } ;

/* Variables and functions */
 int ESM_APU_16BITLINEAR ; 
 int ESM_APU_8BITLINEAR ; 
 int ESM_HIRQ_DSIE ; 
 scalar_t__ ESM_PORT_HOST_IRQ ; 
 int ESS_FMT_16BIT ; 
 int ESS_FMT_STEREO ; 
 int /*<<< orphan*/  apu_set_register (struct es1968*,int,int,int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_es1968_apu_set_freq (struct es1968*,int,int) ; 
 int snd_es1968_compute_rate (struct es1968*,int) ; 
 int /*<<< orphan*/  snd_es1968_program_wavecache (struct es1968*,struct esschan*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_es1968_playback_setup(struct es1968 *chip, struct esschan *es,
				      struct snd_pcm_runtime *runtime)
{
	u32 pa;
	int high_apu = 0;
	int channel, apu;
	int i, size;
	unsigned long flags;
	u32 freq;

	size = es->dma_size >> es->wav_shift;

	if (es->fmt & ESS_FMT_STEREO)
		high_apu++;

	for (channel = 0; channel <= high_apu; channel++) {
		apu = es->apu[channel];

		snd_es1968_program_wavecache(chip, es, channel, es->memory->buf.addr, 0);

		/* Offset to PCMBAR */
		pa = es->memory->buf.addr;
		pa -= chip->dma.addr;
		pa >>= 1;	/* words */

		pa |= 0x00400000;	/* System RAM (Bit 22) */

		if (es->fmt & ESS_FMT_STEREO) {
			/* Enable stereo */
			if (channel)
				pa |= 0x00800000;	/* (Bit 23) */
			if (es->fmt & ESS_FMT_16BIT)
				pa >>= 1;
		}

		/* base offset of dma calcs when reading the pointer
		   on this left one */
		es->base[channel] = pa & 0xFFFF;

		for (i = 0; i < 16; i++)
			apu_set_register(chip, apu, i, 0x0000);

		/* Load the buffer into the wave engine */
		apu_set_register(chip, apu, 4, ((pa >> 16) & 0xFF) << 8);
		apu_set_register(chip, apu, 5, pa & 0xFFFF);
		apu_set_register(chip, apu, 6, (pa + size) & 0xFFFF);
		/* setting loop == sample len */
		apu_set_register(chip, apu, 7, size);

		/* clear effects/env.. */
		apu_set_register(chip, apu, 8, 0x0000);
		/* set amp now to 0xd0 (?), low byte is 'amplitude dest'? */
		apu_set_register(chip, apu, 9, 0xD000);

		/* clear routing stuff */
		apu_set_register(chip, apu, 11, 0x0000);
		/* dma on, no envelopes, filter to all 1s) */
		apu_set_register(chip, apu, 0, 0x400F);

		if (es->fmt & ESS_FMT_16BIT)
			es->apu_mode[channel] = ESM_APU_16BITLINEAR;
		else
			es->apu_mode[channel] = ESM_APU_8BITLINEAR;

		if (es->fmt & ESS_FMT_STEREO) {
			/* set panning: left or right */
			/* Check: different panning. On my Canyon 3D Chipset the
			   Channels are swapped. I don't know, about the output
			   to the SPDif Link. Perhaps you have to change this
			   and not the APU Regs 4-5. */
			apu_set_register(chip, apu, 10,
					 0x8F00 | (channel ? 0 : 0x10));
			es->apu_mode[channel] += 1;	/* stereo */
		} else
			apu_set_register(chip, apu, 10, 0x8F08);
	}

	spin_lock_irqsave(&chip->reg_lock, flags);
	/* clear WP interrupts */
	outw(1, chip->io_port + 0x04);
	/* enable WP ints */
	outw(inw(chip->io_port + ESM_PORT_HOST_IRQ) | ESM_HIRQ_DSIE, chip->io_port + ESM_PORT_HOST_IRQ);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	freq = runtime->rate;
	/* set frequency */
	if (freq > 48000)
		freq = 48000;
	if (freq < 4000)
		freq = 4000;

	/* hmmm.. */
	if (!(es->fmt & ESS_FMT_16BIT) && !(es->fmt & ESS_FMT_STEREO))
		freq >>= 1;

	freq = snd_es1968_compute_rate(chip, freq);

	/* Load the frequency, turn on 6dB */
	snd_es1968_apu_set_freq(chip, es->apu[0], freq);
	snd_es1968_apu_set_freq(chip, es->apu[1], freq);
}