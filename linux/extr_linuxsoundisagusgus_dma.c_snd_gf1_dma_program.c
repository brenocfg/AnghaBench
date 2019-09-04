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
struct TYPE_2__ {int dma1; scalar_t__ enh_mode; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 unsigned char SNDRV_GF1_DMA_16BIT ; 
 unsigned short SNDRV_GF1_DMA_ENABLE ; 
 unsigned char SNDRV_GF1_DMA_READ ; 
 unsigned char SNDRV_GF1_DMA_WIDTH16 ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_DRAM_DMA_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_DRAM_DMA_HIGH ; 
 int /*<<< orphan*/  SNDRV_GF1_GW_DRAM_DMA_LOW ; 
 int /*<<< orphan*/  snd_dma_program (int,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_dma_ack (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_write16 (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_printd (char*,unsigned int) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned int,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_gf1_dma_program(struct snd_gus_card * gus,
				unsigned int addr,
				unsigned long buf_addr,
				unsigned int count,
				unsigned int cmd)
{
	unsigned long flags;
	unsigned int address;
	unsigned char dma_cmd;
	unsigned int address_high;

	snd_printdd("dma_transfer: addr=0x%x, buf=0x%lx, count=0x%x\n",
		    addr, buf_addr, count);

	if (gus->gf1.dma1 > 3) {
		if (gus->gf1.enh_mode) {
			address = addr >> 1;
		} else {
			if (addr & 0x1f) {
				snd_printd("snd_gf1_dma_transfer: unaligned address (0x%x)?\n", addr);
				return;
			}
			address = (addr & 0x000c0000) | ((addr & 0x0003ffff) >> 1);
		}
	} else {
		address = addr;
	}

	dma_cmd = SNDRV_GF1_DMA_ENABLE | (unsigned short) cmd;
#if 0
	dma_cmd |= 0x08;
#endif
	if (dma_cmd & SNDRV_GF1_DMA_16BIT) {
		count++;
		count &= ~1;	/* align */
	}
	if (gus->gf1.dma1 > 3) {
		dma_cmd |= SNDRV_GF1_DMA_WIDTH16;
		count++;
		count &= ~1;	/* align */
	}
	snd_gf1_dma_ack(gus);
	snd_dma_program(gus->gf1.dma1, buf_addr, count, dma_cmd & SNDRV_GF1_DMA_READ ? DMA_MODE_READ : DMA_MODE_WRITE);
#if 0
	snd_printk(KERN_DEBUG "address = 0x%x, count = 0x%x, dma_cmd = 0x%x\n",
		   address << 1, count, dma_cmd);
#endif
	spin_lock_irqsave(&gus->reg_lock, flags);
	if (gus->gf1.enh_mode) {
		address_high = ((address >> 16) & 0x000000f0) | (address & 0x0000000f);
		snd_gf1_write16(gus, SNDRV_GF1_GW_DRAM_DMA_LOW, (unsigned short) (address >> 4));
		snd_gf1_write8(gus, SNDRV_GF1_GB_DRAM_DMA_HIGH, (unsigned char) address_high);
	} else
		snd_gf1_write16(gus, SNDRV_GF1_GW_DRAM_DMA_LOW, (unsigned short) (address >> 4));
	snd_gf1_write8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL, dma_cmd);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
}