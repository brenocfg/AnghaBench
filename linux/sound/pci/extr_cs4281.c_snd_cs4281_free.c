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
struct cs4281 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  ba1; int /*<<< orphan*/  ba0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA0_HIMR ; 
 int /*<<< orphan*/  BA0_SSPM ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct cs4281*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cs4281*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4281_free_gameport (struct cs4281*) ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 

__attribute__((used)) static int snd_cs4281_free(struct cs4281 *chip)
{
	snd_cs4281_free_gameport(chip);

	if (chip->irq >= 0)
		synchronize_irq(chip->irq);

	/* Mask interrupts */
	snd_cs4281_pokeBA0(chip, BA0_HIMR, 0x7fffffff);
	/* Stop the DLL Clock logic. */
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, 0);
	/* Sound System Power Management - Turn Everything OFF */
	snd_cs4281_pokeBA0(chip, BA0_SSPM, 0);
	/* PCI interface - D3 state */
	pci_set_power_state(chip->pci, PCI_D3hot);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	iounmap(chip->ba0);
	iounmap(chip->ba1);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);

	kfree(chip);
	return 0;
}