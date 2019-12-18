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
struct es1938 {scalar_t__ irq; int /*<<< orphan*/  pci; scalar_t__ rmidi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESSSB_IREG_MPU401CONTROL ; 
 int /*<<< orphan*/  IRQCONTROL ; 
 int /*<<< orphan*/  SLIO_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct es1938*) ; 
 int /*<<< orphan*/  kfree (struct es1938*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1938_free_gameport (struct es1938*) ; 
 int /*<<< orphan*/  snd_es1938_mixer_bits (struct es1938*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_es1938_free(struct es1938 *chip)
{
	/* disable irqs */
	outb(0x00, SLIO_REG(chip, IRQCONTROL));
	if (chip->rmidi)
		snd_es1938_mixer_bits(chip, ESSSB_IREG_MPU401CONTROL, 0x40, 0);

	snd_es1938_free_gameport(chip);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}