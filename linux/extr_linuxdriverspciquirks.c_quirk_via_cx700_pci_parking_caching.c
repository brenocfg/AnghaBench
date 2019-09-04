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
typedef  int uint8_t ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_VIA_8235_USB_2 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_VIA ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void quirk_via_cx700_pci_parking_caching(struct pci_dev *dev)
{
	/*
	 * Disable PCI Bus Parking and PCI Master read caching on CX700
	 * which causes unspecified timing errors with a VT6212L on the PCI
	 * bus leading to USB2.0 packet loss.
	 *
	 * This quirk is only enabled if a second (on the external PCI bus)
	 * VT6212L is found -- the CX700 core itself also contains a USB
	 * host controller with the same PCI ID as the VT6212L.
	 */

	/* Count VT6212L instances */
	struct pci_dev *p = pci_get_device(PCI_VENDOR_ID_VIA,
		PCI_DEVICE_ID_VIA_8235_USB_2, NULL);
	uint8_t b;

	/*
	 * p should contain the first (internal) VT6212L -- see if we have
	 * an external one by searching again.
	 */
	p = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235_USB_2, p);
	if (!p)
		return;
	pci_dev_put(p);

	if (pci_read_config_byte(dev, 0x76, &b) == 0) {
		if (b & 0x40) {
			/* Turn off PCI Bus Parking */
			pci_write_config_byte(dev, 0x76, b ^ 0x40);

			pci_info(dev, "Disabling VIA CX700 PCI parking\n");
		}
	}

	if (pci_read_config_byte(dev, 0x72, &b) == 0) {
		if (b != 0) {
			/* Turn off PCI Master read caching */
			pci_write_config_byte(dev, 0x72, 0x0);

			/* Set PCI Master Bus time-out to "1x16 PCLK" */
			pci_write_config_byte(dev, 0x75, 0x1);

			/* Disable "Read FIFO Timer" */
			pci_write_config_byte(dev, 0x77, 0x0);

			pci_info(dev, "Disabling VIA CX700 PCI caching\n");
		}
	}
}