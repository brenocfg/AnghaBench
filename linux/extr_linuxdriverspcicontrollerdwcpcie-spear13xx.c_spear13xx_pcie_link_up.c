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
struct spear13xx_pcie {struct pcie_app_reg* app_base; } ;
struct pcie_app_reg {int /*<<< orphan*/  app_status_1; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int XMLH_LINK_UP ; 
 int readl (int /*<<< orphan*/ *) ; 
 struct spear13xx_pcie* to_spear13xx_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int spear13xx_pcie_link_up(struct dw_pcie *pci)
{
	struct spear13xx_pcie *spear13xx_pcie = to_spear13xx_pcie(pci);
	struct pcie_app_reg *app_reg = spear13xx_pcie->app_base;

	if (readl(&app_reg->app_status_1) & XMLH_LINK_UP)
		return 1;

	return 0;
}