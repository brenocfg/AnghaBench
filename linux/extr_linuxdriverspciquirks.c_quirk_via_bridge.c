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
struct pci_dev {int device; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_VIA_8231 135 
#define  PCI_DEVICE_ID_VIA_8233A 134 
#define  PCI_DEVICE_ID_VIA_8233C_0 133 
#define  PCI_DEVICE_ID_VIA_8233_0 132 
#define  PCI_DEVICE_ID_VIA_8235 131 
#define  PCI_DEVICE_ID_VIA_8237 130 
#define  PCI_DEVICE_ID_VIA_8237A 129 
#define  PCI_DEVICE_ID_VIA_82C686 128 
 void* PCI_SLOT (int /*<<< orphan*/ ) ; 
 void* via_vlink_dev_hi ; 
 int via_vlink_dev_lo ; 

__attribute__((used)) static void quirk_via_bridge(struct pci_dev *dev)
{
	/* See what bridge we have and find the device ranges */
	switch (dev->device) {
	case PCI_DEVICE_ID_VIA_82C686:
		/*
		 * The VT82C686 is special; it attaches to PCI and can have
		 * any device number. All its subdevices are functions of
		 * that single device.
		 */
		via_vlink_dev_lo = PCI_SLOT(dev->devfn);
		via_vlink_dev_hi = PCI_SLOT(dev->devfn);
		break;
	case PCI_DEVICE_ID_VIA_8237:
	case PCI_DEVICE_ID_VIA_8237A:
		via_vlink_dev_lo = 15;
		break;
	case PCI_DEVICE_ID_VIA_8235:
		via_vlink_dev_lo = 16;
		break;
	case PCI_DEVICE_ID_VIA_8231:
	case PCI_DEVICE_ID_VIA_8233_0:
	case PCI_DEVICE_ID_VIA_8233A:
	case PCI_DEVICE_ID_VIA_8233C_0:
		via_vlink_dev_lo = 17;
		break;
	}
}