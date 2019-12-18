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
typedef  int u32 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned short dma_addr; } ;
struct snd_als300 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLAYBACK_CONTROL ; 
 int /*<<< orphan*/  PLAYBACK_END ; 
 int /*<<< orphan*/  PLAYBACK_START ; 
 int TRANSFER_START ; 
 int /*<<< orphan*/  snd_als300_dbgplay (char*,unsigned short,unsigned short) ; 
 int snd_als300_gcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als300_gcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 unsigned short snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 unsigned short snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_als300* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_als300_playback_prepare(struct snd_pcm_substream *substream)
{
	u32 tmp;
	struct snd_als300 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned short period_bytes = snd_pcm_lib_period_bytes(substream);
	unsigned short buffer_bytes = snd_pcm_lib_buffer_bytes(substream);
	
	spin_lock_irq(&chip->reg_lock);
	tmp = snd_als300_gcr_read(chip->port, PLAYBACK_CONTROL);
	tmp &= ~TRANSFER_START;

	snd_als300_dbgplay("Period bytes: %d Buffer bytes %d\n",
						period_bytes, buffer_bytes);
	
	/* set block size */
	tmp &= 0xffff0000;
	tmp |= period_bytes - 1;
	snd_als300_gcr_write(chip->port, PLAYBACK_CONTROL, tmp);

	/* set dma area */
	snd_als300_gcr_write(chip->port, PLAYBACK_START,
					runtime->dma_addr);
	snd_als300_gcr_write(chip->port, PLAYBACK_END,
					runtime->dma_addr + buffer_bytes - 1);
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}