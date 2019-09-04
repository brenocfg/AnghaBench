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
typedef  int /*<<< orphan*/  u8 ;
struct pci_priv {int /*<<< orphan*/  linkctrl_reg; } ;
struct pci_dev {int dummy; } ;
struct dvobj_priv {struct pci_priv pcipriv; struct pci_dev* ppcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int PCI_EXP_LNKCTL ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_pci_parse_configuration(struct dvobj_priv *dvobj)
{
	struct pci_dev	*pdev = dvobj->ppcidev;
	struct pci_priv	*pcipriv = &(dvobj->pcipriv);
	u8 tmp;
	int pos;
	u8 linkctrl_reg;

	//Link Control Register
	pos = pci_find_capability(pdev, PCI_CAP_ID_EXP);
	pci_read_config_byte(pdev, pos + PCI_EXP_LNKCTL, &linkctrl_reg);
	pcipriv->linkctrl_reg = linkctrl_reg;

	//DBG_871X("Link Control Register = %x\n", pcipriv->linkctrl_reg);

	pci_read_config_byte(pdev, 0x98, &tmp);
	tmp |= BIT(4);
	pci_write_config_byte(pdev, 0x98, tmp);

	//tmp = 0x17;
	//pci_write_config_byte(pdev, 0x70f, tmp);
}