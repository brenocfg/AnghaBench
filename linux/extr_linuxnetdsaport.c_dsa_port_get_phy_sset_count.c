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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct dsa_port {int /*<<< orphan*/  dn; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR_OR_NULL (struct phy_device*) ; 
 struct phy_device* dsa_port_get_phy_device (struct dsa_port*) ; 
 scalar_t__ of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 
 int phy_ethtool_get_sset_count (struct phy_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

int dsa_port_get_phy_sset_count(struct dsa_port *dp)
{
	struct phy_device *phydev;
	int ret = -EOPNOTSUPP;

	if (of_phy_is_fixed_link(dp->dn))
		return ret;

	phydev = dsa_port_get_phy_device(dp);
	if (IS_ERR_OR_NULL(phydev))
		return ret;

	ret = phy_ethtool_get_sset_count(phydev);
	put_device(&phydev->mdio.dev);

	return ret;
}