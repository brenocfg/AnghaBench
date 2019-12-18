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
struct snd_sb {int capture_format; int /*<<< orphan*/  mixer_lock; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int ALS4000_FORMAT_16BIT ; 
 int /*<<< orphan*/  ALS4K_CR1C_FIFO2_BLOCK_LENGTH_LO ; 
 int /*<<< orphan*/  ALS4K_CR1D_FIFO2_BLOCK_LENGTH_HI ; 
 int snd_als4000_get_format (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_als4000_set_capture_dma (struct snd_sb*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  snd_als4000_set_rate (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als4_cr_write (struct snd_sb*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_als4000_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long size;
	unsigned count;

	chip->capture_format = snd_als4000_get_format(runtime);
		
	size = snd_pcm_lib_buffer_bytes(substream);
	count = snd_pcm_lib_period_bytes(substream);
	
	if (chip->capture_format & ALS4000_FORMAT_16BIT)
		count >>= 1;
	count--;

	spin_lock_irq(&chip->reg_lock);
	snd_als4000_set_rate(chip, runtime->rate);
	snd_als4000_set_capture_dma(chip, runtime->dma_addr, size);
	spin_unlock_irq(&chip->reg_lock);
	spin_lock_irq(&chip->mixer_lock);
	snd_als4_cr_write(chip, ALS4K_CR1C_FIFO2_BLOCK_LENGTH_LO, count & 0xff);
	snd_als4_cr_write(chip, ALS4K_CR1D_FIFO2_BLOCK_LENGTH_HI, count >> 8);
	spin_unlock_irq(&chip->mixer_lock);
	return 0;
}