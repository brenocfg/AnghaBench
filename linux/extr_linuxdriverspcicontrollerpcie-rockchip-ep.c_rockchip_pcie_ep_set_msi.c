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
typedef  int u8 ;
typedef  int u16 ;
struct rockchip_pcie {int dummy; } ;
struct rockchip_pcie_ep {struct rockchip_pcie rockchip; } ;
struct pci_epc {int dummy; } ;

/* Variables and functions */
 int PCI_MSI_FLAGS_64BIT ; 
 scalar_t__ ROCKCHIP_PCIE_EP_FUNC_BASE (int) ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MASK_MSI_CAP ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_MASK ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_OFFSET ; 
 scalar_t__ ROCKCHIP_PCIE_EP_MSI_CTRL_REG ; 
 struct rockchip_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int rockchip_pcie_read (struct rockchip_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_ep_set_msi(struct pci_epc *epc, u8 fn,
				    u8 multi_msg_cap)
{
	struct rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	struct rockchip_pcie *rockchip = &ep->rockchip;
	u16 flags;

	flags = rockchip_pcie_read(rockchip,
				   ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	flags &= ~ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_MASK;
	flags |=
	   ((multi_msg_cap << 1) <<  ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_OFFSET) |
	   PCI_MSI_FLAGS_64BIT;
	flags &= ~ROCKCHIP_PCIE_EP_MSI_CTRL_MASK_MSI_CAP;
	rockchip_pcie_write(rockchip, flags,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	return 0;
}