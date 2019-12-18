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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  format; int /*<<< orphan*/  dma_addr; } ;
struct es1938 {unsigned int dma1_size; int dma1_shift; int /*<<< orphan*/  dma1_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC1 ; 
 int /*<<< orphan*/  ESS_CMD_ANALOGCONTROL ; 
 int /*<<< orphan*/  ESS_CMD_DMACNTRELOADH ; 
 int /*<<< orphan*/  ESS_CMD_DMACNTRELOADL ; 
 int /*<<< orphan*/  ESS_CMD_SETFORMAT ; 
 int /*<<< orphan*/  ESS_CMD_SETFORMAT2 ; 
 int /*<<< orphan*/  snd_es1938_bits (struct es1938*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_es1938_playback2_setdma (struct es1938*) ; 
 int /*<<< orphan*/  snd_es1938_rate_set (struct es1938*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1938_reset_fifo (struct es1938*) ; 
 int /*<<< orphan*/  snd_es1938_write (struct es1938*,int /*<<< orphan*/ ,int) ; 
 int snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_playback2_prepare(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int u, is8, mono;
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	unsigned int count = snd_pcm_lib_period_bytes(substream);

	chip->dma1_size = size;
	chip->dma1_start = runtime->dma_addr;

	mono = (runtime->channels > 1) ? 0 : 1;
	is8 = snd_pcm_format_width(runtime->format) == 16 ? 0 : 1;
	u = snd_pcm_format_unsigned(runtime->format);

	chip->dma1_shift = 2 - mono - is8;

	count = 0x10000 - count;
 
	/* reset */
	snd_es1938_reset_fifo(chip);
	
	snd_es1938_bits(chip, ESS_CMD_ANALOGCONTROL, 0x03, (mono ? 2 : 1));

	/* set clock and counters */
        snd_es1938_rate_set(chip, substream, DAC1);
	snd_es1938_write(chip, ESS_CMD_DMACNTRELOADL, count & 0xff);
	snd_es1938_write(chip, ESS_CMD_DMACNTRELOADH, count >> 8);

	/* initialized and configure DAC */
        snd_es1938_write(chip, ESS_CMD_SETFORMAT, u ? 0x80 : 0x00);
        snd_es1938_write(chip, ESS_CMD_SETFORMAT, u ? 0x51 : 0x71);
        snd_es1938_write(chip, ESS_CMD_SETFORMAT2, 
			 0x90 | (mono ? 0x40 : 0x08) |
			 (is8 ? 0x00 : 0x04) | (u ? 0x00 : 0x20));

	/* program DMA */
	snd_es1938_playback2_setdma(chip);
	
	return 0;
}