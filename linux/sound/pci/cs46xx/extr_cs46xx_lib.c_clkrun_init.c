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
typedef  int u8 ;
struct snd_cs46xx {int acpi_port; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82371AB_3 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 

__attribute__((used)) static void clkrun_init(struct snd_cs46xx *chip)
{
	struct pci_dev *pdev;
	u8 pp;

	chip->acpi_port = 0;
	
	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
		PCI_DEVICE_ID_INTEL_82371AB_3, NULL);
	if (pdev == NULL)
		return;		/* Not a thinkpad thats for sure */

	/* Find the control port */		
	pci_read_config_byte(pdev, 0x41, &pp);
	chip->acpi_port = pp << 8;
	pci_dev_put(pdev);
}