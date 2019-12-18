#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_runtime {int rate; } ;
struct esschan {int dma_size; int wav_shift; int* apu; int fmt; TYPE_4__* memory; TYPE_2__* mixbuf; } ;
struct es1968 {int /*<<< orphan*/  reg_lock; scalar_t__ io_port; } ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ buf; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESM_APU_INPUTMIXER ; 
 int /*<<< orphan*/  ESM_APU_SRCONVERTOR ; 
 int ESM_HIRQ_DSIE ; 
 int ESM_MIXBUF_SIZE ; 
 scalar_t__ ESM_PORT_HOST_IRQ ; 
 int ESS_FMT_STEREO ; 
 int /*<<< orphan*/  init_capture_apu (struct es1968*,struct esschan*,int,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_es1968_apu_set_freq (struct es1968*,int,int) ; 
 int snd_es1968_compute_rate (struct es1968*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_es1968_capture_setup(struct es1968 *chip, struct esschan *es,
				     struct snd_pcm_runtime *runtime)
{
	int size;
	u32 freq;
	unsigned long flags;

	size = es->dma_size >> es->wav_shift;

	/* APU assignments:
	   0 = mono/left SRC
	   1 = right SRC
	   2 = mono/left Input Mixer
	   3 = right Input Mixer
	*/
	/* data seems to flow from the codec, through an apu into
	   the 'mixbuf' bit of page, then through the SRC apu
	   and out to the real 'buffer'.  ok.  sure.  */

	/* input mixer (left/mono) */
	/* parallel in crap, see maestro reg 0xC [8-11] */
	init_capture_apu(chip, es, 2,
			 es->mixbuf->buf.addr, ESM_MIXBUF_SIZE/4, /* in words */
			 ESM_APU_INPUTMIXER, 0x14);
	/* SRC (left/mono); get input from inputing apu */
	init_capture_apu(chip, es, 0, es->memory->buf.addr, size,
			 ESM_APU_SRCONVERTOR, es->apu[2]);
	if (es->fmt & ESS_FMT_STEREO) {
		/* input mixer (right) */
		init_capture_apu(chip, es, 3,
				 es->mixbuf->buf.addr + ESM_MIXBUF_SIZE/2,
				 ESM_MIXBUF_SIZE/4, /* in words */
				 ESM_APU_INPUTMIXER, 0x15);
		/* SRC (right) */
		init_capture_apu(chip, es, 1,
				 es->memory->buf.addr + size*2, size,
				 ESM_APU_SRCONVERTOR, es->apu[3]);
	}

	freq = runtime->rate;
	/* Sample Rate conversion APUs don't like 0x10000 for their rate */
	if (freq > 47999)
		freq = 47999;
	if (freq < 4000)
		freq = 4000;

	freq = snd_es1968_compute_rate(chip, freq);

	/* Load the frequency, turn on 6dB */
	snd_es1968_apu_set_freq(chip, es->apu[0], freq);
	snd_es1968_apu_set_freq(chip, es->apu[1], freq);

	/* fix mixer rate at 48khz.  and its _must_ be 0x10000. */
	freq = 0x10000;
	snd_es1968_apu_set_freq(chip, es->apu[2], freq);
	snd_es1968_apu_set_freq(chip, es->apu[3], freq);

	spin_lock_irqsave(&chip->reg_lock, flags);
	/* clear WP interrupts */
	outw(1, chip->io_port + 0x04);
	/* enable WP ints */
	outw(inw(chip->io_port + ESM_PORT_HOST_IRQ) | ESM_HIRQ_DSIE, chip->io_port + ESM_PORT_HOST_IRQ);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}