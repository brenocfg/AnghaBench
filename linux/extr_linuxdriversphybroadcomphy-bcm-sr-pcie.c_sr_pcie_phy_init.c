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
struct sr_pcie_phy {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ pcie_core_is_for_rc (struct sr_pcie_phy*) ; 
 struct sr_pcie_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int sr_pcie_phy_init(struct phy *p)
{
	struct sr_pcie_phy *phy = phy_get_drvdata(p);

	/*
	 * Check whether this PHY is for root complex or not. If yes, return
	 * zero so the host driver can proceed to enumeration. If not, return
	 * an error and that will force the host driver to bail out
	 */
	if (pcie_core_is_for_rc(phy))
		return 0;

	return -ENODEV;
}