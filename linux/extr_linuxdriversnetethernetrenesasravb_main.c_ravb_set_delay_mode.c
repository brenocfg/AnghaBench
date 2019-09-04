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
struct ravb_private {scalar_t__ phy_interface; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APSR ; 
 int /*<<< orphan*/  APSR_DM ; 
 int APSR_DM_RDM ; 
 int APSR_DM_TDM ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ravb_set_delay_mode(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int set = 0;

	if (priv->phy_interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    priv->phy_interface == PHY_INTERFACE_MODE_RGMII_RXID)
		set |= APSR_DM_RDM;

	if (priv->phy_interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    priv->phy_interface == PHY_INTERFACE_MODE_RGMII_TXID)
		set |= APSR_DM_TDM;

	ravb_modify(ndev, APSR, APSR_DM, set);
}