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
struct pcie_port {int dummy; } ;
struct dw_pcie {int dummy; } ;
struct armada8k_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  armada8k_pcie_establish_link (struct armada8k_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 struct armada8k_pcie* to_armada8k_pcie (struct dw_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 

__attribute__((used)) static int armada8k_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct armada8k_pcie *pcie = to_armada8k_pcie(pci);

	dw_pcie_setup_rc(pp);
	armada8k_pcie_establish_link(pcie);

	return 0;
}