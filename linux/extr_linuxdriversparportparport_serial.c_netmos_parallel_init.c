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
struct pci_dev {scalar_t__ device; scalar_t__ subsystem_vendor; int subsystem_device; } ;
struct parport_pc_pci {int numports; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ PCI_DEVICE_ID_NETMOS_9835 ; 
 scalar_t__ PCI_DEVICE_ID_NETMOS_9912 ; 
 scalar_t__ PCI_VENDOR_ID_IBM ; 

__attribute__((used)) static int netmos_parallel_init(struct pci_dev *dev, struct parport_pc_pci *par,
				int autoirq, int autodma)
{
	/* the rule described below doesn't hold for this device */
	if (dev->device == PCI_DEVICE_ID_NETMOS_9835 &&
			dev->subsystem_vendor == PCI_VENDOR_ID_IBM &&
			dev->subsystem_device == 0x0299)
		return -ENODEV;

	if (dev->device == PCI_DEVICE_ID_NETMOS_9912) {
		par->numports = 1;
	} else {
		/*
		 * Netmos uses the subdevice ID to indicate the number of parallel
		 * and serial ports.  The form is 0x00PS, where <P> is the number of
		 * parallel ports and <S> is the number of serial ports.
		 */
		par->numports = (dev->subsystem_device & 0xf0) >> 4;
		if (par->numports > ARRAY_SIZE(par->addr))
			par->numports = ARRAY_SIZE(par->addr);
	}

	return 0;
}