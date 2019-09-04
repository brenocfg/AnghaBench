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
typedef  scalar_t__ u8 ;
struct pci_priv {scalar_t__ pcibridge_linkctrlreg; scalar_t__ pcibridge_pciehdr_offset; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct dvobj_priv {struct pci_dev* ppcidev; struct pci_priv pcipriv; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void rtw_pci_get_linkcontrol_field(struct dvobj_priv *dvobj)
{
	struct pci_priv	*pcipriv = &(dvobj->pcipriv);
	struct pci_dev	*pdev = dvobj->ppcidev;
	struct pci_dev	*bridge_pdev = pdev->bus->self;
	u8	capabilityoffset = pcipriv->pcibridge_pciehdr_offset;
	u8	linkctrl_reg;

	/*Read  Link Control Register*/
	pci_read_config_byte(bridge_pdev, capabilityoffset + PCI_EXP_LNKCTL, &linkctrl_reg);

	pcipriv->pcibridge_linkctrlreg = linkctrl_reg;
}