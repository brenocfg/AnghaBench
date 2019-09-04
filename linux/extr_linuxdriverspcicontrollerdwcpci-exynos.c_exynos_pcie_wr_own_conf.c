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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port {int dummy; } ;
struct exynos_pcie {int dummy; } ;
struct dw_pcie {scalar_t__ dbi_base; } ;

/* Variables and functions */
 int dw_pcie_write (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pcie_sideband_dbi_w_mode (struct exynos_pcie*,int) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct exynos_pcie* to_exynos_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int exynos_pcie_wr_own_conf(struct pcie_port *pp, int where, int size,
				u32 val)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct exynos_pcie *ep = to_exynos_pcie(pci);
	int ret;

	exynos_pcie_sideband_dbi_w_mode(ep, true);
	ret = dw_pcie_write(pci->dbi_base + where, size, val);
	exynos_pcie_sideband_dbi_w_mode(ep, false);
	return ret;
}