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
struct ls_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {scalar_t__ dbi_base; } ;

/* Variables and functions */
 scalar_t__ PCIE_ABSERR ; 
 int /*<<< orphan*/  PCIE_ABSERR_SETTING ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ls_pcie_fix_error_response(struct ls_pcie *pcie)
{
	struct dw_pcie *pci = pcie->pci;

	iowrite32(PCIE_ABSERR_SETTING, pci->dbi_base + PCIE_ABSERR);
}