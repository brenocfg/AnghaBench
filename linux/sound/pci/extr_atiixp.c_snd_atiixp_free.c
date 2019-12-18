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
struct atiixp {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct atiixp*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct atiixp*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_atiixp_chip_stop (struct atiixp*) ; 

__attribute__((used)) static int snd_atiixp_free(struct atiixp *chip)
{
	if (chip->irq < 0)
		goto __hw_end;
	snd_atiixp_chip_stop(chip);

      __hw_end:
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	iounmap(chip->remap_addr);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}