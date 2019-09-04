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
typedef  int /*<<< orphan*/  u32 ;
struct pci_epf_bar {int barno; int /*<<< orphan*/  flags; } ;
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {int /*<<< orphan*/  ib_window_map; int /*<<< orphan*/ * bar_to_atu; } ;
struct dw_pcie {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int /*<<< orphan*/  DW_PCIE_REGION_INBOUND ; 
 int /*<<< orphan*/  __dw_pcie_ep_reset_bar (struct dw_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_disable_atu (struct dw_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static void dw_pcie_ep_clear_bar(struct pci_epc *epc, u8 func_no,
				 struct pci_epf_bar *epf_bar)
{
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	enum pci_barno bar = epf_bar->barno;
	u32 atu_index = ep->bar_to_atu[bar];

	__dw_pcie_ep_reset_bar(pci, bar, epf_bar->flags);

	dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_INBOUND);
	clear_bit(atu_index, ep->ib_window_map);
}