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
struct es1938 {unsigned int dma2_size; int dma2_shift; int /*<<< orphan*/  dma2_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC2 ; 
 int /*<<< orphan*/  ESSSB_IREG_AUDIO2CONTROL2 ; 
 int /*<<< orphan*/  ESSSB_IREG_AUDIO2TCOUNTH ; 
 int /*<<< orphan*/  ESSSB_IREG_AUDIO2TCOUNTL ; 
 int /*<<< orphan*/  snd_es1938_mixer_write (struct es1938*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_es1938_playback1_setdma (struct es1938*) ; 
 int /*<<< orphan*/  snd_es1938_rate_set (struct es1938*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1938_reset_fifo (struct es1938*) ; 
 int snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_playback1_prepare(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int u, is8, mono;
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	unsigned int count = snd_pcm_lib_period_bytes(substream);

	chip->dma2_size = size;
	chip->dma2_start = runtime->dma_addr;

	mono = (runtime->channels > 1) ? 0 : 1;
	is8 = snd_pcm_format_width(runtime->format) == 16 ? 0 : 1;
	u = snd_pcm_format_unsigned(runtime->format);

	chip->dma2_shift = 2 - mono - is8;

        snd_es1938_reset_fifo(chip);

	/* set clock and counters */
        snd_es1938_rate_set(chip, substream, DAC2);

	count >>= 1;
	count = 0x10000 - count;
	snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2TCOUNTL, count & 0xff);
	snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2TCOUNTH, count >> 8);

	/* initialize and configure Audio 2 DAC */
	snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2CONTROL2, 0x40 | (u ? 0 : 4) |
			       (mono ? 0 : 2) | (is8 ? 0 : 1));

	/* program DMA */
	snd_es1938_playback1_setdma(chip);
	
	return 0;
}