#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int devices_in_package; } ;
struct phy_device {TYPE_2__ mdio; TYPE_1__ c45_ids; int /*<<< orphan*/  is_c45; } ;
struct mv3310_priv {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MDIO_DEVS_AN ; 
 int MDIO_DEVS_PMAPMD ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct mv3310_priv*) ; 
 struct mv3310_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mv3310_hwmon_probe (struct phy_device*) ; 

__attribute__((used)) static int mv3310_probe(struct phy_device *phydev)
{
	struct mv3310_priv *priv;
	u32 mmd_mask = MDIO_DEVS_PMAPMD | MDIO_DEVS_AN;
	int ret;

	if (!phydev->is_c45 ||
	    (phydev->c45_ids.devices_in_package & mmd_mask) != mmd_mask)
		return -ENODEV;

	priv = devm_kzalloc(&phydev->mdio.dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev_set_drvdata(&phydev->mdio.dev, priv);

	ret = mv3310_hwmon_probe(phydev);
	if (ret)
		return ret;

	return 0;
}