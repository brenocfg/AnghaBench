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
struct pci_dev {int subsystem_device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_HP_DIVA_EVEREST 135 
#define  PCI_DEVICE_ID_HP_DIVA_HALFDOME 134 
#define  PCI_DEVICE_ID_HP_DIVA_HURRICANE 133 
#define  PCI_DEVICE_ID_HP_DIVA_KEYSTONE 132 
#define  PCI_DEVICE_ID_HP_DIVA_MAESTRO 131 
#define  PCI_DEVICE_ID_HP_DIVA_POWERBAR 130 
#define  PCI_DEVICE_ID_HP_DIVA_TOSCA1 129 
#define  PCI_DEVICE_ID_HP_DIVA_TOSCA2 128 

__attribute__((used)) static int pci_hp_diva_init(struct pci_dev *dev)
{
	int rc = 0;

	switch (dev->subsystem_device) {
	case PCI_DEVICE_ID_HP_DIVA_TOSCA1:
	case PCI_DEVICE_ID_HP_DIVA_HALFDOME:
	case PCI_DEVICE_ID_HP_DIVA_KEYSTONE:
	case PCI_DEVICE_ID_HP_DIVA_EVEREST:
		rc = 3;
		break;
	case PCI_DEVICE_ID_HP_DIVA_TOSCA2:
		rc = 2;
		break;
	case PCI_DEVICE_ID_HP_DIVA_MAESTRO:
		rc = 4;
		break;
	case PCI_DEVICE_ID_HP_DIVA_POWERBAR:
	case PCI_DEVICE_ID_HP_DIVA_HURRICANE:
		rc = 1;
		break;
	}

	return rc;
}