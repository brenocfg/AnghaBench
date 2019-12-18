#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct atiixp_modem {scalar_t__ remap_addr; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  pci; } ;
struct atiixp_dma_desc {unsigned int size; void* next; scalar_t__ status; void* addr; } ;
struct TYPE_6__ {scalar_t__ addr; int /*<<< orphan*/ * area; } ;
struct atiixp_dma {unsigned int period_bytes; unsigned int periods; TYPE_2__* ops; TYPE_3__ desc_buf; } ;
struct TYPE_5__ {scalar_t__ llp_offset; int /*<<< orphan*/  (* enable_dma ) (struct atiixp_modem*,int) ;} ;
struct TYPE_4__ {scalar_t__ dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_DESC_LIST_SIZE ; 
 unsigned int ATI_MAX_DESCRIPTORS ; 
 int ATI_REG_LINKPTR_EN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct atiixp_modem*,int) ; 
 int /*<<< orphan*/  stub2 (struct atiixp_modem*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int atiixp_build_dma_packets(struct atiixp_modem *chip,
				    struct atiixp_dma *dma,
				    struct snd_pcm_substream *substream,
				    unsigned int periods,
				    unsigned int period_bytes)
{
	unsigned int i;
	u32 addr, desc_addr;
	unsigned long flags;

	if (periods > ATI_MAX_DESCRIPTORS)
		return -ENOMEM;

	if (dma->desc_buf.area == NULL) {
		if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(chip->pci),
					ATI_DESC_LIST_SIZE, &dma->desc_buf) < 0)
			return -ENOMEM;
		dma->period_bytes = dma->periods = 0; /* clear */
	}

	if (dma->periods == periods && dma->period_bytes == period_bytes)
		return 0;

	/* reset DMA before changing the descriptor table */
	spin_lock_irqsave(&chip->reg_lock, flags);
	writel(0, chip->remap_addr + dma->ops->llp_offset);
	dma->ops->enable_dma(chip, 0);
	dma->ops->enable_dma(chip, 1);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	/* fill the entries */
	addr = (u32)substream->runtime->dma_addr;
	desc_addr = (u32)dma->desc_buf.addr;
	for (i = 0; i < periods; i++) {
		struct atiixp_dma_desc *desc;
		desc = &((struct atiixp_dma_desc *)dma->desc_buf.area)[i];
		desc->addr = cpu_to_le32(addr);
		desc->status = 0;
		desc->size = period_bytes >> 2; /* in dwords */
		desc_addr += sizeof(struct atiixp_dma_desc);
		if (i == periods - 1)
			desc->next = cpu_to_le32((u32)dma->desc_buf.addr);
		else
			desc->next = cpu_to_le32(desc_addr);
		addr += period_bytes;
	}

	writel((u32)dma->desc_buf.addr | ATI_REG_LINKPTR_EN,
	       chip->remap_addr + dma->ops->llp_offset);

	dma->period_bytes = period_bytes;
	dma->periods = periods;

	return 0;
}