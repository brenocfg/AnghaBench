#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_5__ {int bytes; int addr; int /*<<< orphan*/ * area; } ;
struct TYPE_4__ {TYPE_2__ etram_pages; } ;
struct snd_emu10k1 {int /*<<< orphan*/  emu_lock; scalar_t__ port; TYPE_1__ fx8010; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ HCFG ; 
 int HCFG_LOCKTANKCACHE_MASK ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  TCB ; 
 int /*<<< orphan*/  TCBS ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 scalar_t__ snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_emu10k1_fx8010_tram_setup(struct snd_emu10k1 *emu, u32 size)
{
	u8 size_reg = 0;

	/* size is in samples */
	if (size != 0) {
		size = (size - 1) >> 13;

		while (size) {
			size >>= 1;
			size_reg++;
		}
		size = 0x2000 << size_reg;
	}
	if ((emu->fx8010.etram_pages.bytes / 2) == size)
		return 0;
	spin_lock_irq(&emu->emu_lock);
	outl(HCFG_LOCKTANKCACHE_MASK | inl(emu->port + HCFG), emu->port + HCFG);
	spin_unlock_irq(&emu->emu_lock);
	snd_emu10k1_ptr_write(emu, TCB, 0, 0);
	snd_emu10k1_ptr_write(emu, TCBS, 0, 0);
	if (emu->fx8010.etram_pages.area != NULL) {
		snd_dma_free_pages(&emu->fx8010.etram_pages);
		emu->fx8010.etram_pages.area = NULL;
		emu->fx8010.etram_pages.bytes = 0;
	}

	if (size > 0) {
		if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(emu->pci),
					size * 2, &emu->fx8010.etram_pages) < 0)
			return -ENOMEM;
		memset(emu->fx8010.etram_pages.area, 0, size * 2);
		snd_emu10k1_ptr_write(emu, TCB, 0, emu->fx8010.etram_pages.addr);
		snd_emu10k1_ptr_write(emu, TCBS, 0, size_reg);
		spin_lock_irq(&emu->emu_lock);
		outl(inl(emu->port + HCFG) & ~HCFG_LOCKTANKCACHE_MASK, emu->port + HCFG);
		spin_unlock_irq(&emu->emu_lock);
	}

	return 0;
}