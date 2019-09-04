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
struct cdns_pcie {int phy_count; int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

void cdns_pcie_disable_phy(struct cdns_pcie *pcie)
{
	int i = pcie->phy_count;

	while (i--) {
		phy_power_off(pcie->phy[i]);
		phy_exit(pcie->phy[i]);
	}
}