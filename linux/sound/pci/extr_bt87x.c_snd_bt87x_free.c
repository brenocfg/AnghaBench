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
struct snd_bt87x {scalar_t__ irq; int /*<<< orphan*/  pci; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_bt87x*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct snd_bt87x*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_bt87x_stop (struct snd_bt87x*) ; 

__attribute__((used)) static int snd_bt87x_free(struct snd_bt87x *chip)
{
	if (chip->mmio)
		snd_bt87x_stop(chip);
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	iounmap(chip->mmio);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}