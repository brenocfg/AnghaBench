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
struct hdac_bus {int irq; } ;
struct azx {scalar_t__ msi; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int azx_acquire_irq (struct azx*,int) ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 int /*<<< orphan*/  free_irq (int,struct azx*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disable_msi_reset_irq(struct azx *chip)
{
	struct hdac_bus *bus = azx_bus(chip);
	int err;

	free_irq(bus->irq, chip);
	bus->irq = -1;
	pci_disable_msi(chip->pci);
	chip->msi = 0;
	err = azx_acquire_irq(chip, 1);
	if (err < 0)
		return err;

	return 0;
}