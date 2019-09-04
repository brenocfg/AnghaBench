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
typedef  scalar_t__ u32 ;
struct dw_pcie_ep {scalar_t__ num_ib_windows; int /*<<< orphan*/  ib_window_map; scalar_t__* bar_to_atu; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;
typedef  enum dw_pcie_as_type { ____Placeholder_dw_pcie_as_type } dw_pcie_as_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dw_pcie_prog_inbound_atu (struct dw_pcie*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static int dw_pcie_ep_inbound_atu(struct dw_pcie_ep *ep, enum pci_barno bar,
				  dma_addr_t cpu_addr,
				  enum dw_pcie_as_type as_type)
{
	int ret;
	u32 free_win;
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	free_win = find_first_zero_bit(ep->ib_window_map, ep->num_ib_windows);
	if (free_win >= ep->num_ib_windows) {
		dev_err(pci->dev, "No free inbound window\n");
		return -EINVAL;
	}

	ret = dw_pcie_prog_inbound_atu(pci, free_win, bar, cpu_addr,
				       as_type);
	if (ret < 0) {
		dev_err(pci->dev, "Failed to program IB window\n");
		return ret;
	}

	ep->bar_to_atu[bar] = free_win;
	set_bit(free_win, ep->ib_window_map);

	return 0;
}