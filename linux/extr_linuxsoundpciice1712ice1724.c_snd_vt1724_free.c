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
struct snd_ice1712 {scalar_t__ irq; struct snd_ice1712* spec; int /*<<< orphan*/  pci; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_INT_MASK ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQMASK ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_ice1712*) ; 
 int /*<<< orphan*/  kfree (struct snd_ice1712*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_akm4xxx_free (struct snd_ice1712*) ; 

__attribute__((used)) static int snd_vt1724_free(struct snd_ice1712 *ice)
{
	if (!ice->port)
		goto __hw_end;
	/* mask all interrupts */
	outb(0xff, ICEMT1724(ice, DMA_INT_MASK));
	outb(0xff, ICEREG1724(ice, IRQMASK));
	/* --- */
__hw_end:
	if (ice->irq >= 0)
		free_irq(ice->irq, ice);
	pci_release_regions(ice->pci);
	snd_ice1712_akm4xxx_free(ice);
	pci_disable_device(ice->pci);
	kfree(ice->spec);
	kfree(ice);
	return 0;
}