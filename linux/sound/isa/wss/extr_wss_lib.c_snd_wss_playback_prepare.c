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
struct snd_wss {unsigned int p_dma_size; int* image; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  dma1; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_PLAYBACK_ENABLE ; 
 int CS4231_PLAYBACK_PIO ; 
 size_t CS4231_PLAYBK_FORMAT ; 
 int /*<<< orphan*/  CS4231_PLY_LWR_CNT ; 
 int /*<<< orphan*/  CS4231_PLY_UPR_CNT ; 
 int DMA_AUTOINIT ; 
 int DMA_MODE_WRITE ; 
 int /*<<< orphan*/  snd_dma_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_wss* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_wss_debug (struct snd_wss*) ; 
 int snd_wss_get_count (int,unsigned int) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_wss_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_wss *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long flags;
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	unsigned int count = snd_pcm_lib_period_bytes(substream);

	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->p_dma_size = size;
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO);
	snd_dma_program(chip->dma1, runtime->dma_addr, size, DMA_MODE_WRITE | DMA_AUTOINIT);
	count = snd_wss_get_count(chip->image[CS4231_PLAYBK_FORMAT], count) - 1;
	snd_wss_out(chip, CS4231_PLY_LWR_CNT, (unsigned char) count);
	snd_wss_out(chip, CS4231_PLY_UPR_CNT, (unsigned char) (count >> 8));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
#if 0
	snd_wss_debug(chip);
#endif
	return 0;
}