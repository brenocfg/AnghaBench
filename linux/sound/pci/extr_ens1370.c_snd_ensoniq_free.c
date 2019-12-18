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
struct TYPE_2__ {scalar_t__ area; } ;
struct ensoniq {scalar_t__ irq; int /*<<< orphan*/  pci; TYPE_1__ dma_bug; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  ES_1370_SERR_DISABLE ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  SERIAL ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ensoniq*) ; 
 int /*<<< orphan*/  kfree (struct ensoniq*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_ensoniq_free_gameport (struct ensoniq*) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 

__attribute__((used)) static int snd_ensoniq_free(struct ensoniq *ensoniq)
{
	snd_ensoniq_free_gameport(ensoniq);
	if (ensoniq->irq < 0)
		goto __hw_end;
#ifdef CHIP1370
	outl(ES_1370_SERR_DISABLE, ES_REG(ensoniq, CONTROL));	/* switch everything off */
	outl(0, ES_REG(ensoniq, SERIAL));	/* clear serial interface */
#else
	outl(0, ES_REG(ensoniq, CONTROL));	/* switch everything off */
	outl(0, ES_REG(ensoniq, SERIAL));	/* clear serial interface */
#endif
	if (ensoniq->irq >= 0)
		synchronize_irq(ensoniq->irq);
	pci_set_power_state(ensoniq->pci, PCI_D3hot);
      __hw_end:
#ifdef CHIP1370
	if (ensoniq->dma_bug.area)
		snd_dma_free_pages(&ensoniq->dma_bug);
#endif
	if (ensoniq->irq >= 0)
		free_irq(ensoniq->irq, ensoniq);
	pci_release_regions(ensoniq->pci);
	pci_disable_device(ensoniq->pci);
	kfree(ensoniq);
	return 0;
}