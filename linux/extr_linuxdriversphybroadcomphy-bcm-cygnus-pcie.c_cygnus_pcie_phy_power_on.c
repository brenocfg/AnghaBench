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
struct phy {int dummy; } ;
struct cygnus_pcie_phy {int dummy; } ;

/* Variables and functions */
 int cygnus_pcie_power_config (struct cygnus_pcie_phy*,int) ; 
 struct cygnus_pcie_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int cygnus_pcie_phy_power_on(struct phy *p)
{
	struct cygnus_pcie_phy *phy = phy_get_drvdata(p);

	return cygnus_pcie_power_config(phy, true);
}