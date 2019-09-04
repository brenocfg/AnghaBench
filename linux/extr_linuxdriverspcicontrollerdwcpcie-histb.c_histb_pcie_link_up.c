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
typedef  int u32 ;
struct histb_pcie {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int PCIE_LTSSM_STATE_ACTIVE ; 
 int PCIE_LTSSM_STATE_MASK ; 
 int PCIE_RDLH_LINK_UP ; 
 int /*<<< orphan*/  PCIE_SYS_STAT0 ; 
 int /*<<< orphan*/  PCIE_SYS_STAT4 ; 
 int PCIE_XMLH_LINK_UP ; 
 int histb_pcie_readl (struct histb_pcie*,int /*<<< orphan*/ ) ; 
 struct histb_pcie* to_histb_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int histb_pcie_link_up(struct dw_pcie *pci)
{
	struct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 regval;
	u32 status;

	regval = histb_pcie_readl(hipcie, PCIE_SYS_STAT0);
	status = histb_pcie_readl(hipcie, PCIE_SYS_STAT4);
	status &= PCIE_LTSSM_STATE_MASK;
	if ((regval & PCIE_XMLH_LINK_UP) && (regval & PCIE_RDLH_LINK_UP) &&
	    (status == PCIE_LTSSM_STATE_ACTIVE))
		return 1;

	return 0;
}