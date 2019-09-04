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
struct sis7019 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  ioaddr; scalar_t__ ioport; } ;

/* Variables and functions */
 scalar_t__ SIS_GCR ; 
 int /*<<< orphan*/  SIS_GCR_SOFTWARE_RESET ; 
 scalar_t__ SIS_GIER ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct sis7019*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_free_suspend (struct sis7019*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sis_chip_free(struct sis7019 *sis)
{
	/* Reset the chip, and disable all interrputs.
	 */
	outl(SIS_GCR_SOFTWARE_RESET, sis->ioport + SIS_GCR);
	udelay(25);
	outl(0, sis->ioport + SIS_GCR);
	outl(0, sis->ioport + SIS_GIER);

	/* Now, free everything we allocated.
	 */
	if (sis->irq >= 0)
		free_irq(sis->irq, sis);

	iounmap(sis->ioaddr);
	pci_release_regions(sis->pci);
	pci_disable_device(sis->pci);
	sis_free_suspend(sis);
	return 0;
}