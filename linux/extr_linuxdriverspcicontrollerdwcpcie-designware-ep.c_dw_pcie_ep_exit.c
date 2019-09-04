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
struct pci_epc {TYPE_1__* mem; } ;
struct dw_pcie_ep {int /*<<< orphan*/  msi_mem; int /*<<< orphan*/  msi_mem_phys; struct pci_epc* epc; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_epc_mem_exit (struct pci_epc*) ; 
 int /*<<< orphan*/  pci_epc_mem_free_addr (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dw_pcie_ep_exit(struct dw_pcie_ep *ep)
{
	struct pci_epc *epc = ep->epc;

	pci_epc_mem_free_addr(epc, ep->msi_mem_phys, ep->msi_mem,
			      epc->mem->page_size);

	pci_epc_mem_exit(epc);
}