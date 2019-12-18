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
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  format; } ;
struct snd_es18xx {int /*<<< orphan*/  dma1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1 ; 
 int DMA_AUTOINIT ; 
 int DMA_MODE_READ ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  snd_dma_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  snd_es18xx_bits (struct snd_es18xx*,int,int,int) ; 
 int /*<<< orphan*/  snd_es18xx_rate_set (struct snd_es18xx*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es18xx_reset_fifo (struct snd_es18xx*) ; 
 int /*<<< orphan*/  snd_es18xx_write (struct snd_es18xx*,int,int) ; 
 scalar_t__ snd_pcm_format_unsigned (int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es18xx_capture_prepare(struct snd_pcm_substream *substream)
{
        struct snd_es18xx *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	unsigned int count = snd_pcm_lib_period_bytes(substream);

	snd_es18xx_reset_fifo(chip);

        /* Set stereo/mono */
        snd_es18xx_bits(chip, 0xA8, 0x03, runtime->channels == 1 ? 0x02 : 0x01);

        snd_es18xx_rate_set(chip, substream, ADC1);

        /* Transfer Count Reload */
	count = 0x10000 - count;
	snd_es18xx_write(chip, 0xA4, count & 0xff);
	snd_es18xx_write(chip, 0xA5, count >> 8);

#ifdef AVOID_POPS
	mdelay(100);
#endif

        /* Set format */
        snd_es18xx_write(chip, 0xB7, 
                         snd_pcm_format_unsigned(runtime->format) ? 0x51 : 0x71);
        snd_es18xx_write(chip, 0xB7, 0x90 |
                         ((runtime->channels == 1) ? 0x40 : 0x08) |
                         (snd_pcm_format_width(runtime->format) == 16 ? 0x04 : 0x00) |
                         (snd_pcm_format_unsigned(runtime->format) ? 0x00 : 0x20));

        /* Set DMA controller */
        snd_dma_program(chip->dma1, runtime->dma_addr, size, DMA_MODE_READ | DMA_AUTOINIT);

	return 0;
}