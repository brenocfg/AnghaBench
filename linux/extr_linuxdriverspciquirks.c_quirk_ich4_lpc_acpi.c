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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ICH4_ACPI_EN ; 
 int /*<<< orphan*/  ICH4_GPIOBASE ; 
 int /*<<< orphan*/  ICH4_GPIO_CNTL ; 
 int ICH4_GPIO_EN ; 
 int /*<<< orphan*/  ICH_ACPI_CNTL ; 
 int /*<<< orphan*/  ICH_PMBASE ; 
 scalar_t__ PCI_BRIDGE_RESOURCES ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  quirk_io_region (struct pci_dev*,int /*<<< orphan*/ ,int,scalar_t__,char*) ; 

__attribute__((used)) static void quirk_ich4_lpc_acpi(struct pci_dev *dev)
{
	u8 enable;

	/*
	 * The check for PCIBIOS_MIN_IO is to ensure we won't create a conflict
	 * with low legacy (and fixed) ports. We don't know the decoding
	 * priority and can't tell whether the legacy device or the one created
	 * here is really at that address.  This happens on boards with broken
	 * BIOSes.
	 */
	pci_read_config_byte(dev, ICH_ACPI_CNTL, &enable);
	if (enable & ICH4_ACPI_EN)
		quirk_io_region(dev, ICH_PMBASE, 128, PCI_BRIDGE_RESOURCES,
				 "ICH4 ACPI/GPIO/TCO");

	pci_read_config_byte(dev, ICH4_GPIO_CNTL, &enable);
	if (enable & ICH4_GPIO_EN)
		quirk_io_region(dev, ICH4_GPIOBASE, 64, PCI_BRIDGE_RESOURCES+1,
				"ICH4 GPIO");
}