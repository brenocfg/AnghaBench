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
struct snd_device {struct aw2* device_data; } ;
struct aw2 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  iobase_virt; int /*<<< orphan*/  saa7146; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aw2*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_aw2_saa7146_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_aw2_dev_free(struct snd_device *device)
{
	struct aw2 *chip = device->device_data;

	/* Free hardware */
	snd_aw2_saa7146_free(&chip->saa7146);

	/* release the irq */
	if (chip->irq >= 0)
		free_irq(chip->irq, (void *)chip);
	/* release the i/o ports & memory */
	iounmap(chip->iobase_virt);
	pci_release_regions(chip->pci);
	/* disable the PCI entry */
	pci_disable_device(chip->pci);
	/* release the data */
	kfree(chip);

	return 0;
}