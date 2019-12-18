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
struct via82xx_modem {scalar_t__ irq; unsigned int num_devs; int /*<<< orphan*/  pci; int /*<<< orphan*/ * devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct via82xx_modem*) ; 
 int /*<<< orphan*/  kfree (struct via82xx_modem*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_channel_reset (struct via82xx_modem*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_via82xx_free(struct via82xx_modem *chip)
{
	unsigned int i;

	if (chip->irq < 0)
		goto __end_hw;
	/* disable interrupts */
	for (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

      __end_hw:
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}