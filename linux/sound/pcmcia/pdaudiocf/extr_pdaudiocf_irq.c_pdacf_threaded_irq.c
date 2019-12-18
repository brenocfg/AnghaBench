#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pdacf {int chip_status; unsigned long port; int pcm_frame; int pcm_hwptr; int pcm_size; int pcm_tdone; int pcm_period; int /*<<< orphan*/  reg_lock; TYPE_1__* pcm_substream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/ * runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long PDAUDIOCF_REG_MD ; 
 unsigned long PDAUDIOCF_REG_RDP ; 
 unsigned long PDAUDIOCF_REG_WDP ; 
 int PDAUDIOCF_STAT_IS_CONFIGURED ; 
 int PDAUDIOCF_STAT_IS_STALE ; 
 int inw (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdacf_transfer (struct snd_pdacf*,int,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_pcm_running (TYPE_1__*) ; 

irqreturn_t pdacf_threaded_irq(int irq, void *dev)
{
	struct snd_pdacf *chip = dev;
	int size, off, cont, rdp, wdp;

	if ((chip->chip_status & (PDAUDIOCF_STAT_IS_STALE|PDAUDIOCF_STAT_IS_CONFIGURED)) != PDAUDIOCF_STAT_IS_CONFIGURED)
		return IRQ_HANDLED;
	
	if (chip->pcm_substream == NULL || chip->pcm_substream->runtime == NULL || !snd_pcm_running(chip->pcm_substream))
		return IRQ_HANDLED;

	rdp = inw(chip->port + PDAUDIOCF_REG_RDP);
	wdp = inw(chip->port + PDAUDIOCF_REG_WDP);
	/* printk(KERN_DEBUG "TASKLET: rdp = %x, wdp = %x\n", rdp, wdp); */
	size = wdp - rdp;
	if (size < 0)
		size += 0x10000;
	if (size == 0)
		size = 0x10000;
	size /= chip->pcm_frame;
	if (size > 64)
		size -= 32;

#if 0
	chip->pcm_hwptr += size;
	chip->pcm_hwptr %= chip->pcm_size;
	chip->pcm_tdone += size;
	if (chip->pcm_frame == 2) {
		unsigned long rdp_port = chip->port + PDAUDIOCF_REG_MD;
		while (size-- > 0) {
			inw(rdp_port);
			inw(rdp_port);
		}
	} else {
		unsigned long rdp_port = chip->port + PDAUDIOCF_REG_MD;
		while (size-- > 0) {
			inw(rdp_port);
			inw(rdp_port);
			inw(rdp_port);
		}
	}
#else
	off = chip->pcm_hwptr + chip->pcm_tdone;
	off %= chip->pcm_size;
	chip->pcm_tdone += size;
	while (size > 0) {
		cont = chip->pcm_size - off;
		if (cont > size)
			cont = size;
		pdacf_transfer(chip, cont, off);
		off += cont;
		off %= chip->pcm_size;
		size -= cont;
	}
#endif
	mutex_lock(&chip->reg_lock);
	while (chip->pcm_tdone >= chip->pcm_period) {
		chip->pcm_hwptr += chip->pcm_period;
		chip->pcm_hwptr %= chip->pcm_size;
		chip->pcm_tdone -= chip->pcm_period;
		mutex_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(chip->pcm_substream);
		mutex_lock(&chip->reg_lock);
	}
	mutex_unlock(&chip->reg_lock);
	return IRQ_HANDLED;
}