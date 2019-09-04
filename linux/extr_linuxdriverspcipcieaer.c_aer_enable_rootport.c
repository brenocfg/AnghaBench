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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int aer_cap; } ;
struct aer_rpc {struct pci_dev* rpd; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_COR_STATUS ; 
 scalar_t__ PCI_ERR_ROOT_COMMAND ; 
 scalar_t__ PCI_ERR_ROOT_STATUS ; 
 scalar_t__ PCI_ERR_UNCOR_STATUS ; 
 int /*<<< orphan*/  PCI_EXP_DEVSTA ; 
 int /*<<< orphan*/  PCI_EXP_RTCTL ; 
 int /*<<< orphan*/  ROOT_PORT_INTR_ON_MESG_MASK ; 
 int /*<<< orphan*/  SYSTEM_ERROR_INTR_ON_MESG_MASK ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_downstream_devices_error_reporting (struct pci_dev*,int) ; 

__attribute__((used)) static void aer_enable_rootport(struct aer_rpc *rpc)
{
	struct pci_dev *pdev = rpc->rpd;
	int aer_pos;
	u16 reg16;
	u32 reg32;

	/* Clear PCIe Capability's Device Status */
	pcie_capability_read_word(pdev, PCI_EXP_DEVSTA, &reg16);
	pcie_capability_write_word(pdev, PCI_EXP_DEVSTA, reg16);

	/* Disable system error generation in response to error messages */
	pcie_capability_clear_word(pdev, PCI_EXP_RTCTL,
				   SYSTEM_ERROR_INTR_ON_MESG_MASK);

	aer_pos = pdev->aer_cap;
	/* Clear error status */
	pci_read_config_dword(pdev, aer_pos + PCI_ERR_ROOT_STATUS, &reg32);
	pci_write_config_dword(pdev, aer_pos + PCI_ERR_ROOT_STATUS, reg32);
	pci_read_config_dword(pdev, aer_pos + PCI_ERR_COR_STATUS, &reg32);
	pci_write_config_dword(pdev, aer_pos + PCI_ERR_COR_STATUS, reg32);
	pci_read_config_dword(pdev, aer_pos + PCI_ERR_UNCOR_STATUS, &reg32);
	pci_write_config_dword(pdev, aer_pos + PCI_ERR_UNCOR_STATUS, reg32);

	/*
	 * Enable error reporting for the root port device and downstream port
	 * devices.
	 */
	set_downstream_devices_error_reporting(pdev, true);

	/* Enable Root Port's interrupt in response to error messages */
	pci_read_config_dword(pdev, aer_pos + PCI_ERR_ROOT_COMMAND, &reg32);
	reg32 |= ROOT_PORT_INTR_ON_MESG_MASK;
	pci_write_config_dword(pdev, aer_pos + PCI_ERR_ROOT_COMMAND, reg32);
}