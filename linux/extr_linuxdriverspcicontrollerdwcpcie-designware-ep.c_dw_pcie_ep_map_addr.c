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
typedef  int /*<<< orphan*/  u64 ;
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {int dummy; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dw_pcie_ep_outbound_atu (struct dw_pcie_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static int dw_pcie_ep_map_addr(struct pci_epc *epc, u8 func_no,
			       phys_addr_t addr,
			       u64 pci_addr, size_t size)
{
	int ret;
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	ret = dw_pcie_ep_outbound_atu(ep, addr, pci_addr, size);
	if (ret) {
		dev_err(pci->dev, "Failed to enable address\n");
		return ret;
	}

	return 0;
}