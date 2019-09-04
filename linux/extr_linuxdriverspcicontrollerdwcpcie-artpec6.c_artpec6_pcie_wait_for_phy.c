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
struct artpec6_pcie {int variant; } ;

/* Variables and functions */
#define  ARTPEC6 129 
#define  ARTPEC7 128 
 int /*<<< orphan*/  artpec6_pcie_wait_for_phy_a6 (struct artpec6_pcie*) ; 
 int /*<<< orphan*/  artpec6_pcie_wait_for_phy_a7 (struct artpec6_pcie*) ; 

__attribute__((used)) static void artpec6_pcie_wait_for_phy(struct artpec6_pcie *artpec6_pcie)
{
	switch (artpec6_pcie->variant) {
	case ARTPEC6:
		artpec6_pcie_wait_for_phy_a6(artpec6_pcie);
		break;
	case ARTPEC7:
		artpec6_pcie_wait_for_phy_a7(artpec6_pcie);
		break;
	}
}