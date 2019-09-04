#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct pci_bus {int cur_bus_speed; } ;
struct controller {TYPE_1__* pci_dev; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;
struct TYPE_2__ {struct pci_bus* subordinate; } ;

/* Variables and functions */
 int ENODEV ; 
 int PCI_SPEED_100MHz_PCIX ; 
 int PCI_SPEED_100MHz_PCIX_266 ; 
 int PCI_SPEED_100MHz_PCIX_533 ; 
 int PCI_SPEED_100MHz_PCIX_ECC ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_133MHz_PCIX_266 ; 
 int PCI_SPEED_133MHz_PCIX_533 ; 
 int PCI_SPEED_133MHz_PCIX_ECC ; 
 int PCI_SPEED_33MHz ; 
 int PCI_SPEED_66MHz ; 
 int PCI_SPEED_66MHz_PCIX ; 
 int PCI_SPEED_66MHz_PCIX_266 ; 
 int PCI_SPEED_66MHz_PCIX_533 ; 
 int PCI_SPEED_66MHz_PCIX_ECC ; 
 int PCI_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  PROG_INTERFACE ; 
 int /*<<< orphan*/  SEC_BUS_CONFIG ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int shpc_readb (struct controller*,int /*<<< orphan*/ ) ; 
 int shpc_readw (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shpc_get_cur_bus_speed(struct controller *ctrl)
{
	int retval = 0;
	struct pci_bus *bus = ctrl->pci_dev->subordinate;
	enum pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u16 sec_bus_reg = shpc_readw(ctrl, SEC_BUS_CONFIG);
	u8 pi = shpc_readb(ctrl, PROG_INTERFACE);
	u8 speed_mode = (pi == 2) ? (sec_bus_reg & 0xF) : (sec_bus_reg & 0x7);

	if ((pi == 1) && (speed_mode > 4)) {
		retval = -ENODEV;
		goto out;
	}

	switch (speed_mode) {
	case 0x0:
		bus_speed = PCI_SPEED_33MHz;
		break;
	case 0x1:
		bus_speed = PCI_SPEED_66MHz;
		break;
	case 0x2:
		bus_speed = PCI_SPEED_66MHz_PCIX;
		break;
	case 0x3:
		bus_speed = PCI_SPEED_100MHz_PCIX;
		break;
	case 0x4:
		bus_speed = PCI_SPEED_133MHz_PCIX;
		break;
	case 0x5:
		bus_speed = PCI_SPEED_66MHz_PCIX_ECC;
		break;
	case 0x6:
		bus_speed = PCI_SPEED_100MHz_PCIX_ECC;
		break;
	case 0x7:
		bus_speed = PCI_SPEED_133MHz_PCIX_ECC;
		break;
	case 0x8:
		bus_speed = PCI_SPEED_66MHz_PCIX_266;
		break;
	case 0x9:
		bus_speed = PCI_SPEED_100MHz_PCIX_266;
		break;
	case 0xa:
		bus_speed = PCI_SPEED_133MHz_PCIX_266;
		break;
	case 0xb:
		bus_speed = PCI_SPEED_66MHz_PCIX_533;
		break;
	case 0xc:
		bus_speed = PCI_SPEED_100MHz_PCIX_533;
		break;
	case 0xd:
		bus_speed = PCI_SPEED_133MHz_PCIX_533;
		break;
	default:
		retval = -ENODEV;
		break;
	}

 out:
	bus->cur_bus_speed = bus_speed;
	dbg("Current bus speed = %d\n", bus_speed);
	return retval;
}