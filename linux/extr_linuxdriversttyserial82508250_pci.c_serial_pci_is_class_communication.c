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
struct pci_dev {int class; } ;

/* Variables and functions */
 int ENODEV ; 
 int PCI_CLASS_COMMUNICATION_MODEM ; 
 int PCI_CLASS_COMMUNICATION_MULTISERIAL ; 
 int PCI_CLASS_COMMUNICATION_SERIAL ; 

__attribute__((used)) static int serial_pci_is_class_communication(struct pci_dev *dev)
{
	/*
	 * If it is not a communications device or the programming
	 * interface is greater than 6, give up.
	 */
	if ((((dev->class >> 8) != PCI_CLASS_COMMUNICATION_SERIAL) &&
	     ((dev->class >> 8) != PCI_CLASS_COMMUNICATION_MULTISERIAL) &&
	     ((dev->class >> 8) != PCI_CLASS_COMMUNICATION_MODEM)) ||
	    (dev->class & 0xff) > 6)
		return -ENODEV;

	return 0;
}