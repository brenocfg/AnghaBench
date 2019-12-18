#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int addr; } ;
struct snd_ymfpci {int /*<<< orphan*/  reg_lock; TYPE_1__*** bank_effect; TYPE_2__ ac3_tmp_base; int /*<<< orphan*/  pci; } ;
struct TYPE_3__ {void* loop_end; void* base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  YDSXGR_MAPOFEFFECT ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_ac3_init(struct snd_ymfpci *chip)
{
	if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(chip->pci),
				4096, &chip->ac3_tmp_base) < 0)
		return -ENOMEM;

	chip->bank_effect[3][0]->base =
	chip->bank_effect[3][1]->base = cpu_to_le32(chip->ac3_tmp_base.addr);
	chip->bank_effect[3][0]->loop_end =
	chip->bank_effect[3][1]->loop_end = cpu_to_le32(1024);
	chip->bank_effect[4][0]->base =
	chip->bank_effect[4][1]->base = cpu_to_le32(chip->ac3_tmp_base.addr + 2048);
	chip->bank_effect[4][0]->loop_end =
	chip->bank_effect[4][1]->loop_end = cpu_to_le32(1024);

	spin_lock_irq(&chip->reg_lock);
	snd_ymfpci_writel(chip, YDSXGR_MAPOFEFFECT,
			  snd_ymfpci_readl(chip, YDSXGR_MAPOFEFFECT) | 3 << 3);
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}