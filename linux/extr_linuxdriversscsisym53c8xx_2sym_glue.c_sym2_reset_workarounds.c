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
typedef  int u_short ;
struct sym_chip {int features; } ;
struct pci_dev {int /*<<< orphan*/  revision; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int FE_66MHZ ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_66MHZ ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct sym_chip* sym_lookup_chip_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym2_reset_workarounds(struct pci_dev *pdev)
{
	u_short status_reg;
	struct sym_chip *chip;

	chip = sym_lookup_chip_table(pdev->device, pdev->revision);

	/* Work around for errant bit in 895A, in a fashion
	 * similar to what is done in sym_set_workarounds().
	 */
	pci_read_config_word(pdev, PCI_STATUS, &status_reg);
	if (!(chip->features & FE_66MHZ) && (status_reg & PCI_STATUS_66MHZ)) {
		status_reg = PCI_STATUS_66MHZ;
		pci_write_config_word(pdev, PCI_STATUS, status_reg);
		pci_read_config_word(pdev, PCI_STATUS, &status_reg);
	}
}