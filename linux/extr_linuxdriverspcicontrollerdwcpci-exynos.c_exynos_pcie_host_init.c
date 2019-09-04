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
struct exynos_pcie {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_pcie_enable_interrupts (struct exynos_pcie*) ; 
 int /*<<< orphan*/  exynos_pcie_establish_link (struct exynos_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct exynos_pcie* to_exynos_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int exynos_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct exynos_pcie *ep = to_exynos_pcie(pci);

	exynos_pcie_establish_link(ep);
	exynos_pcie_enable_interrupts(ep);

	return 0;
}