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
struct snd_pcm_runtime {int channels; scalar_t__ buffer_size; scalar_t__ period_size; unsigned int dma_addr; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct cs4281_dma {int valDMR; int valDCR; scalar_t__ regDBA; scalar_t__ regDBC; int left_slot; int right_slot; scalar_t__ regFCR; int valFCR; scalar_t__ regFSIC; int /*<<< orphan*/  fifo_offset; scalar_t__ frag; } ;
struct cs4281 {int src_left_play_slot; int src_right_play_slot; int src_left_rec_slot; int src_right_rec_slot; TYPE_1__* dma; } ;
struct TYPE_2__ {int valDMR; } ;

/* Variables and functions */
 scalar_t__ BA0_ADCSR ; 
 scalar_t__ BA0_DACSR ; 
 int BA0_DCR_HTCIE ; 
 int BA0_DCR_MSK ; 
 int BA0_DCR_TCIE ; 
 int BA0_DMR_AUTO ; 
 int BA0_DMR_BEND ; 
 int BA0_DMR_MONO ; 
 int BA0_DMR_SIZE20 ; 
 int BA0_DMR_SIZE8 ; 
 int BA0_DMR_SWAPC ; 
 int BA0_DMR_TR_READ ; 
 int BA0_DMR_TR_WRITE ; 
 int BA0_DMR_TYPE_SINGLE ; 
 int BA0_DMR_USIGN ; 
 scalar_t__ BA0_FCR0 ; 
 unsigned int BA0_FCR_FEN ; 
 int BA0_FCR_LS (int) ; 
 int BA0_FCR_OF (int /*<<< orphan*/ ) ; 
 unsigned int BA0_FCR_PSH ; 
 int BA0_FCR_RS (int) ; 
 int BA0_FCR_SZ (int /*<<< orphan*/ ) ; 
 scalar_t__ BA0_SRCSA ; 
 int /*<<< orphan*/  CS4281_FIFO_SIZE ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 unsigned int snd_cs4281_peekBA0 (struct cs4281*,scalar_t__) ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,scalar_t__,unsigned int) ; 
 unsigned int snd_cs4281_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_pcm_format_big_endian (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_cs4281_mode(struct cs4281 *chip, struct cs4281_dma *dma,
			    struct snd_pcm_runtime *runtime,
			    int capture, int src)
{
	int rec_mono;

	dma->valDMR = BA0_DMR_TYPE_SINGLE | BA0_DMR_AUTO |
		      (capture ? BA0_DMR_TR_WRITE : BA0_DMR_TR_READ);
	if (runtime->channels == 1)
		dma->valDMR |= BA0_DMR_MONO;
	if (snd_pcm_format_unsigned(runtime->format) > 0)
		dma->valDMR |= BA0_DMR_USIGN;
	if (snd_pcm_format_big_endian(runtime->format) > 0)
		dma->valDMR |= BA0_DMR_BEND;
	switch (snd_pcm_format_width(runtime->format)) {
	case 8: dma->valDMR |= BA0_DMR_SIZE8;
		if (runtime->channels == 1)
			dma->valDMR |= BA0_DMR_SWAPC;
		break;
	case 32: dma->valDMR |= BA0_DMR_SIZE20; break;
	}
	dma->frag = 0;	/* for workaround */
	dma->valDCR = BA0_DCR_TCIE | BA0_DCR_MSK;
	if (runtime->buffer_size != runtime->period_size)
		dma->valDCR |= BA0_DCR_HTCIE;
	/* Initialize DMA */
	snd_cs4281_pokeBA0(chip, dma->regDBA, runtime->dma_addr);
	snd_cs4281_pokeBA0(chip, dma->regDBC, runtime->buffer_size - 1);
	rec_mono = (chip->dma[1].valDMR & BA0_DMR_MONO) == BA0_DMR_MONO;
	snd_cs4281_pokeBA0(chip, BA0_SRCSA, (chip->src_left_play_slot << 0) |
					    (chip->src_right_play_slot << 8) |
					    (chip->src_left_rec_slot << 16) |
					    ((rec_mono ? 31 : chip->src_right_rec_slot) << 24));
	if (!src)
		goto __skip_src;
	if (!capture) {
		if (dma->left_slot == chip->src_left_play_slot) {
			unsigned int val = snd_cs4281_rate(runtime->rate, NULL);
			snd_BUG_ON(dma->right_slot != chip->src_right_play_slot);
			snd_cs4281_pokeBA0(chip, BA0_DACSR, val);
		}
	} else {
		if (dma->left_slot == chip->src_left_rec_slot) {
			unsigned int val = snd_cs4281_rate(runtime->rate, NULL);
			snd_BUG_ON(dma->right_slot != chip->src_right_rec_slot);
			snd_cs4281_pokeBA0(chip, BA0_ADCSR, val);
		}
	}
      __skip_src:
	/* Deactivate wave playback FIFO before changing slot assignments */
	if (dma->regFCR == BA0_FCR0)
		snd_cs4281_pokeBA0(chip, dma->regFCR, snd_cs4281_peekBA0(chip, dma->regFCR) & ~BA0_FCR_FEN);
	/* Initialize FIFO */
	dma->valFCR = BA0_FCR_LS(dma->left_slot) |
		      BA0_FCR_RS(capture && (dma->valDMR & BA0_DMR_MONO) ? 31 : dma->right_slot) |
		      BA0_FCR_SZ(CS4281_FIFO_SIZE) |
		      BA0_FCR_OF(dma->fifo_offset);
	snd_cs4281_pokeBA0(chip, dma->regFCR, dma->valFCR | (capture ? BA0_FCR_PSH : 0));
	/* Activate FIFO again for FM playback */
	if (dma->regFCR == BA0_FCR0)
		snd_cs4281_pokeBA0(chip, dma->regFCR, dma->valFCR | BA0_FCR_FEN);
	/* Clear FIFO Status and Interrupt Control Register */
	snd_cs4281_pokeBA0(chip, dma->regFSIC, 0);
}