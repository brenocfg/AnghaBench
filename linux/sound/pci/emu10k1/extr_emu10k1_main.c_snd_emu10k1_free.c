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
struct TYPE_6__ {scalar_t__ area; } ;
struct TYPE_4__ {int /*<<< orphan*/  firmware_work; } ;
struct snd_emu10k1 {scalar_t__ irq; int /*<<< orphan*/  pci; TYPE_2__* card_capabilities; scalar_t__ port; int /*<<< orphan*/  page_addr_table; int /*<<< orphan*/  page_ptr_table; TYPE_3__ ptb_pages; TYPE_3__ silent_page; int /*<<< orphan*/  memhdr; int /*<<< orphan*/  dock_fw; int /*<<< orphan*/  firmware; TYPE_1__ emu1010; } ;
struct TYPE_5__ {scalar_t__ emu_model; scalar_t__ ca0151_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_HANA_DOCK_PWR ; 
 scalar_t__ EMU_MODEL_EMU1010 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_emu10k1*) ; 
 int /*<<< orphan*/  free_pm_buffer (struct snd_emu10k1*) ; 
 int /*<<< orphan*/  kfree (struct snd_emu10k1*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_emu1010_fpga_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_done (struct snd_emu10k1*) ; 
 int /*<<< orphan*/  snd_emu10k1_free_efx (struct snd_emu10k1*) ; 
 int /*<<< orphan*/  snd_emu10k1_fx8010_tram_setup (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_p16v_free (struct snd_emu10k1*) ; 
 int /*<<< orphan*/  snd_util_memhdr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_emu10k1_free(struct snd_emu10k1 *emu)
{
	if (emu->port) {	/* avoid access to already used hardware */
		snd_emu10k1_fx8010_tram_setup(emu, 0);
		snd_emu10k1_done(emu);
		snd_emu10k1_free_efx(emu);
	}
	if (emu->card_capabilities->emu_model == EMU_MODEL_EMU1010) {
		/* Disable 48Volt power to Audio Dock */
		snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_PWR, 0);
	}
	cancel_delayed_work_sync(&emu->emu1010.firmware_work);
	release_firmware(emu->firmware);
	release_firmware(emu->dock_fw);
	if (emu->irq >= 0)
		free_irq(emu->irq, emu);
	snd_util_memhdr_free(emu->memhdr);
	if (emu->silent_page.area)
		snd_dma_free_pages(&emu->silent_page);
	if (emu->ptb_pages.area)
		snd_dma_free_pages(&emu->ptb_pages);
	vfree(emu->page_ptr_table);
	vfree(emu->page_addr_table);
#ifdef CONFIG_PM_SLEEP
	free_pm_buffer(emu);
#endif
	if (emu->port)
		pci_release_regions(emu->pci);
	if (emu->card_capabilities->ca0151_chip) /* P16V */
		snd_p16v_free(emu);
	pci_disable_device(emu->pci);
	kfree(emu);
	return 0;
}