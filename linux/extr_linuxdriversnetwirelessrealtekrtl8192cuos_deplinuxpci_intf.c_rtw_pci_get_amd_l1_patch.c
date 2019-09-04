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
typedef  int u32 ;
struct pci_dev {TYPE_1__* bus; } ;
struct dvobj_priv {struct pci_dev* ppcidev; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int BIT (int) ; 
 int _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static u8 rtw_pci_get_amd_l1_patch(struct dvobj_priv *dvobj)
{
	struct pci_dev	*pdev = dvobj->ppcidev;
	struct pci_dev	*bridge_pdev = pdev->bus->self;
	u8	status = _FALSE;
	u8	offset_e0;
	u32	offset_e4;

	//NdisRawWritePortUlong(PCI_CONF_ADDRESS,pcicfg_addrport + 0xE0);
	//NdisRawWritePortUchar(PCI_CONF_DATA, 0xA0);
	pci_write_config_byte(bridge_pdev, 0xE0, 0xA0);

	//NdisRawWritePortUlong(PCI_CONF_ADDRESS,pcicfg_addrport + 0xE0);
	//NdisRawReadPortUchar(PCI_CONF_DATA, &offset_e0);
	pci_read_config_byte(bridge_pdev, 0xE0, &offset_e0);

	if (offset_e0 == 0xA0) {
		//NdisRawWritePortUlong(PCI_CONF_ADDRESS, pcicfg_addrport + 0xE4);
		//NdisRawReadPortUlong(PCI_CONF_DATA, &offset_e4);
		pci_read_config_dword(bridge_pdev, 0xE4, &offset_e4);
		if (offset_e4 & BIT(23))
			status = _TRUE;
	}

	return status;
}