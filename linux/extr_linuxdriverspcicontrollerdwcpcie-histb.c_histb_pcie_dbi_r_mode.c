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
struct histb_pcie {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_ELBI_SLV_DBI_ENABLE ; 
 int /*<<< orphan*/  PCIE_SYS_CTRL1 ; 
 int /*<<< orphan*/  histb_pcie_readl (struct histb_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  histb_pcie_writel (struct histb_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct histb_pcie* to_histb_pcie (struct dw_pcie*) ; 

__attribute__((used)) static void histb_pcie_dbi_r_mode(struct pcie_port *pp, bool enable)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 val;

	val = histb_pcie_readl(hipcie, PCIE_SYS_CTRL1);
	if (enable)
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
	else
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
	histb_pcie_writel(hipcie, PCIE_SYS_CTRL1, val);
}