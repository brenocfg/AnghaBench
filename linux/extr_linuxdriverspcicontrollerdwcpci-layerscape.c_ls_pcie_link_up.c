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
typedef  int u32 ;
struct ls_pcie {TYPE_1__* drvdata; scalar_t__ lut; } ;
struct dw_pcie {int dummy; } ;
struct TYPE_2__ {int ltssm_shift; scalar_t__ lut_dbg; } ;

/* Variables and functions */
 int LTSSM_PCIE_L0 ; 
 int LTSSM_STATE_MASK ; 
 int ioread32 (scalar_t__) ; 
 struct ls_pcie* to_ls_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int ls_pcie_link_up(struct dw_pcie *pci)
{
	struct ls_pcie *pcie = to_ls_pcie(pci);
	u32 state;

	state = (ioread32(pcie->lut + pcie->drvdata->lut_dbg) >>
		 pcie->drvdata->ltssm_shift) &
		 LTSSM_STATE_MASK;

	if (state < LTSSM_PCIE_L0)
		return 0;

	return 1;
}