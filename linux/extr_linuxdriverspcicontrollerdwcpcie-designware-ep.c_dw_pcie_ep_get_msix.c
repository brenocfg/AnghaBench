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
typedef  int u32 ;
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {int msix_cap; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCI_MSIX_FLAGS ; 
 int PCI_MSIX_FLAGS_ENABLE ; 
 int PCI_MSIX_FLAGS_QSIZE ; 
 int dw_pcie_readw_dbi (struct dw_pcie*,int) ; 
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static int dw_pcie_ep_get_msix(struct pci_epc *epc, u8 func_no)
{
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	u32 val, reg;

	if (!ep->msix_cap)
		return -EINVAL;

	reg = ep->msix_cap + PCI_MSIX_FLAGS;
	val = dw_pcie_readw_dbi(pci, reg);
	if (!(val & PCI_MSIX_FLAGS_ENABLE))
		return -EINVAL;

	val &= PCI_MSIX_FLAGS_QSIZE;

	return val;
}