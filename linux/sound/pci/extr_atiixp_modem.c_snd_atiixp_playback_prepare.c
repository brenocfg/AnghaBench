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
struct snd_pcm_substream {int dummy; } ;
struct atiixp_modem {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 unsigned int ATI_REG_MODEM_OUT1_DMA_THRESHOLD_MASK ; 
 int ATI_REG_MODEM_OUT1_DMA_THRESHOLD_SHIFT ; 
 int /*<<< orphan*/  MODEM_OUT_FIFO ; 
 unsigned int atiixp_read (struct atiixp_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp_modem*,int /*<<< orphan*/ ,unsigned int) ; 
 struct atiixp_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_atiixp_playback_prepare(struct snd_pcm_substream *substream)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	unsigned int data;

	spin_lock_irq(&chip->reg_lock);
	/* set output threshold */
	data = atiixp_read(chip, MODEM_OUT_FIFO);
	data &= ~ATI_REG_MODEM_OUT1_DMA_THRESHOLD_MASK;
	data |= 0x04 << ATI_REG_MODEM_OUT1_DMA_THRESHOLD_SHIFT;
	atiixp_write(chip, MODEM_OUT_FIFO, data);
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}