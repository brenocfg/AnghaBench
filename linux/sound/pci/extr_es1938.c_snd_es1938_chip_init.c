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
struct es1938 {int ddma_port; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMACLEAR ; 
 int /*<<< orphan*/  IRQCONTROL ; 
 int /*<<< orphan*/  SLDM_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIO_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SL_PCI_CONFIG ; 
 int /*<<< orphan*/  SL_PCI_DDMACONTROL ; 
 int /*<<< orphan*/  SL_PCI_LEGACYCONTROL ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_es1938_reset (struct es1938*) ; 

__attribute__((used)) static void snd_es1938_chip_init(struct es1938 *chip)
{
	/* reset chip */
	snd_es1938_reset(chip);

	/* configure native mode */

	/* enable bus master */
	pci_set_master(chip->pci);

	/* disable legacy audio */
	pci_write_config_word(chip->pci, SL_PCI_LEGACYCONTROL, 0x805f);

	/* set DDMA base */
	pci_write_config_word(chip->pci, SL_PCI_DDMACONTROL, chip->ddma_port | 1);

	/* set DMA/IRQ policy */
	pci_write_config_dword(chip->pci, SL_PCI_CONFIG, 0);

	/* enable Audio 1, Audio 2, MPU401 IRQ and HW volume IRQ*/
	outb(0xf0, SLIO_REG(chip, IRQCONTROL));

	/* reset DMA */
	outb(0, SLDM_REG(chip, DMACLEAR));
}