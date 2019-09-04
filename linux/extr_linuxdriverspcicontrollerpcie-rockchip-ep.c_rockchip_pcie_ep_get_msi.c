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
typedef  int u16 ;
struct rockchip_pcie {int dummy; } ;
struct rockchip_pcie_ep {struct rockchip_pcie rockchip; } ;
struct pci_epc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ROCKCHIP_PCIE_EP_FUNC_BASE (int /*<<< orphan*/ ) ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_ME ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET ; 
 scalar_t__ ROCKCHIP_PCIE_EP_MSI_CTRL_REG ; 
 struct rockchip_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int rockchip_pcie_read (struct rockchip_pcie*,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_ep_get_msi(struct pci_epc *epc, u8 fn)
{
	struct rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	struct rockchip_pcie *rockchip = &ep->rockchip;
	u16 flags;

	flags = rockchip_pcie_read(rockchip,
				   ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	if (!(flags & ROCKCHIP_PCIE_EP_MSI_CTRL_ME))
		return -EINVAL;

	return ((flags & ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK) >>
			ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET);
}