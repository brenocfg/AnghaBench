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
struct spear1310_miphy_priv {scalar_t__ mode; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE ; 
 struct spear1310_miphy_priv* phy_get_drvdata (struct phy*) ; 
 int spear1310_miphy_pcie_init (struct spear1310_miphy_priv*) ; 

__attribute__((used)) static int spear1310_miphy_init(struct phy *phy)
{
	struct spear1310_miphy_priv *priv = phy_get_drvdata(phy);
	int ret = 0;

	if (priv->mode == PCIE)
		ret = spear1310_miphy_pcie_init(priv);

	return ret;
}