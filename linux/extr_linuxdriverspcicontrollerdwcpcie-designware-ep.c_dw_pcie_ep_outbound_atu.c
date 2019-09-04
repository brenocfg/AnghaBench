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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct dw_pcie_ep {size_t num_ob_windows; int /*<<< orphan*/ * outbound_addr; int /*<<< orphan*/  ob_window_map; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCIE_ATU_TYPE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_pcie_prog_outbound_atu (struct dw_pcie*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t find_first_zero_bit (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static int dw_pcie_ep_outbound_atu(struct dw_pcie_ep *ep, phys_addr_t phys_addr,
				   u64 pci_addr, size_t size)
{
	u32 free_win;
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	free_win = find_first_zero_bit(ep->ob_window_map, ep->num_ob_windows);
	if (free_win >= ep->num_ob_windows) {
		dev_err(pci->dev, "No free outbound window\n");
		return -EINVAL;
	}

	dw_pcie_prog_outbound_atu(pci, free_win, PCIE_ATU_TYPE_MEM,
				  phys_addr, pci_addr, size);

	set_bit(free_win, ep->ob_window_map);
	ep->outbound_addr[free_win] = phys_addr;

	return 0;
}