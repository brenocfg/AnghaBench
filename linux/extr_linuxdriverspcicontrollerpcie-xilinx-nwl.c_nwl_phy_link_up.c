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
struct nwl_pcie {scalar_t__ pcireg_base; } ;

/* Variables and functions */
 int PHY_RDY_LINKUP_BIT ; 
 scalar_t__ PS_LINKUP_OFFSET ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool nwl_phy_link_up(struct nwl_pcie *pcie)
{
	if (readl(pcie->pcireg_base + PS_LINKUP_OFFSET) & PHY_RDY_LINKUP_BIT)
		return true;
	return false;
}