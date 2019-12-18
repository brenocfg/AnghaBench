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
struct snd_es1688 {unsigned int dma_size; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  dma8; } ;

/* Variables and functions */
 int DMA_AUTOINIT ; 
 int DMA_MODE_READ ; 
 int /*<<< orphan*/  ES1688_DSP_CMD_SPKOFF ; 
 int /*<<< orphan*/  snd_dma_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  snd_es1688_dsp_command (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int snd_es1688_read (struct snd_es1688*,int) ; 
 int /*<<< orphan*/  snd_es1688_reset (struct snd_es1688*) ; 
 int /*<<< orphan*/  snd_es1688_set_rate (struct snd_es1688*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_es1688_write (struct snd_es1688*,int,unsigned char) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_es1688* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1688_capture_prepare(struct snd_pcm_substream *substream)
{
	unsigned long flags;
	struct snd_es1688 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	unsigned int count = snd_pcm_lib_period_bytes(substream);

	chip->dma_size = size;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_reset(chip);
	snd_es1688_set_rate(chip, substream);
	snd_es1688_dsp_command(chip, ES1688_DSP_CMD_SPKOFF);
	snd_es1688_write(chip, 0xb8, 0x0e);	/* auto init DMA mode */
	snd_es1688_write(chip, 0xa8, (snd_es1688_read(chip, 0xa8) & ~0x03) | (3 - runtime->channels));
	snd_es1688_write(chip, 0xb9, 2);	/* demand mode (4 bytes/request) */
	if (runtime->channels == 1) {
		if (snd_pcm_format_width(runtime->format) == 8) {
			/* 8. bit mono */
			snd_es1688_write(chip, 0xb7, 0x51);
			snd_es1688_write(chip, 0xb7, 0xd0);
		} else {
			/* 16. bit mono */
			snd_es1688_write(chip, 0xb7, 0x71);
			snd_es1688_write(chip, 0xb7, 0xf4);
		}
	} else {
		if (snd_pcm_format_width(runtime->format) == 8) {
			/* 8. bit stereo */
			snd_es1688_write(chip, 0xb7, 0x51);
			snd_es1688_write(chip, 0xb7, 0x98);
		} else {
			/* 16. bit stereo */
			snd_es1688_write(chip, 0xb7, 0x71);
			snd_es1688_write(chip, 0xb7, 0xbc);
		}
	}
	snd_es1688_write(chip, 0xb1, (snd_es1688_read(chip, 0xb1) & 0x0f) | 0x50);
	snd_es1688_write(chip, 0xb2, (snd_es1688_read(chip, 0xb2) & 0x0f) | 0x50);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	/* --- */
	count = -count;
	snd_dma_program(chip->dma8, runtime->dma_addr, size, DMA_MODE_READ | DMA_AUTOINIT);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_write(chip, 0xa4, (unsigned char) count);
	snd_es1688_write(chip, 0xa5, (unsigned char) (count >> 8));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}