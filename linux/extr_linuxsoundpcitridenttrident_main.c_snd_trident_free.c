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
struct TYPE_4__ {scalar_t__ area; } ;
struct TYPE_3__ {TYPE_2__ buffer; int /*<<< orphan*/  shadow_entries; TYPE_2__ silent_page; int /*<<< orphan*/  memhdr; } ;
struct snd_trident {scalar_t__ device; scalar_t__ irq; int /*<<< orphan*/  pci; TYPE_1__ tlb; } ;

/* Variables and functions */
 scalar_t__ NX_SPCTRL_SPCSO ; 
 scalar_t__ NX_TLBC ; 
 scalar_t__ SI_SERIAL_INTF_CTRL ; 
 scalar_t__ TRIDENT_DEVICE_ID_NX ; 
 scalar_t__ TRIDENT_DEVICE_ID_SI7018 ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_trident*) ; 
 int /*<<< orphan*/  kfree (struct snd_trident*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_trident_disable_eso (struct snd_trident*) ; 
 int /*<<< orphan*/  snd_trident_free_gameport (struct snd_trident*) ; 
 int /*<<< orphan*/  snd_util_memhdr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_trident_free(struct snd_trident *trident)
{
	snd_trident_free_gameport(trident);
	snd_trident_disable_eso(trident);
	// Disable S/PDIF out
	if (trident->device == TRIDENT_DEVICE_ID_NX)
		outb(0x00, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));
	else if (trident->device == TRIDENT_DEVICE_ID_SI7018) {
		outl(0, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	}
	if (trident->irq >= 0)
		free_irq(trident->irq, trident);
	if (trident->tlb.buffer.area) {
		outl(0, TRID_REG(trident, NX_TLBC));
		snd_util_memhdr_free(trident->tlb.memhdr);
		if (trident->tlb.silent_page.area)
			snd_dma_free_pages(&trident->tlb.silent_page);
		vfree(trident->tlb.shadow_entries);
		snd_dma_free_pages(&trident->tlb.buffer);
	}
	pci_release_regions(trident->pci);
	pci_disable_device(trident->pci);
	kfree(trident);
	return 0;
}